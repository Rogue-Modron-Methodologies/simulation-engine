#include "Object.h"

void Object::update()
{
	if (body->GetType() == b2BodyType::b2_dynamicBody)
	{
		if (isForceActive && forceDuration > 0)
		{
			body->ApplyForce(activeForce, body->GetWorldPoint(activeForce), true);
			forceDuration -= 5;
		}
		unsigned xVel = abs((int)body->GetLinearVelocity().x);
		unsigned yVel = abs((int)body->GetLinearVelocity().y);
		unsigned rotVel = abs((int)body->GetAngularVelocity());
		unsigned totVel = xVel + yVel + rotVel;
		sprite->setColor(sf::Color(sf::Color::Green));
		/*if (!active && !done && totVel == 0)
		{
		std::cout << "INactive!!!!!!!!!!!!!!!!!!!!!!!!!!!\n";
		}
		else if (!active && !done && totVel > 0)
		{
		active = true;
		std::cout << "Going active\n";
		sprite->setColor(sf::Color(r, g, b, 255));
		}
		else if (active && !done && totVel < 5)
		{
		std::cout << "POP!\n";
		active = false;
		done = true;
		body->SetActive(false);
		sprite->setColor(sf::Color(r, g, b, 0));
		}
		else if (active && !done && totVel > 5)
		{
		sprite->setColor(sf::Color(r, g, b, totVel * 4 % 255));

		}
		*/
	}
	sprite->setPosition(body->GetPosition().x * SCALE, body->GetPosition().y * SCALE);
	sprite->setRotation(180 / b2_pi * body->GetAngle());

}

void Object::draw(sf::RenderWindow &window)
{
	window.draw(*sprite);
}

void Object::applyForce(b2Vec2 force, int duration)
{
	if (body->GetType() == b2_dynamicBody)
	{
		isForceActive = true;
		activeForce = force;
		forceDuration = duration;
	}
	else
		std::cout << "STATIC ";
}

sf::Vector2f Object::convertCoord(sf::RenderWindow &window)
{
	sf::Vector2i pixelPos = sf::Mouse::getPosition(window);
	sf::Vector2f worldPos = window.mapPixelToCoords(pixelPos);
	return worldPos;
}

bool Object::isTargeted(sf::RenderWindow &window)
{
	if (sprite->getGlobalBounds().contains(convertCoord(window)))
		return true;
	else
		return false;
}

void Object::destroy(b2World& world)
{
	world.DestroyBody(body);
	delete sprite;
}