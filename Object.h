#ifndef OBJECT_H
#define OBJECT_H

#include <SFML\Graphics.hpp>
#include <Box2D\Box2D.h>
#include <iostream>

// pixel to real-world conversion
static const float SCALE = 30.f;

// force structure/class
// b2Vec2 force
// double duration
// bool active
// updateForces()

class Object {
protected:
	b2Body* body;
	sf::Sprite* sprite;
	bool isForceActive;
	b2Vec2 activeForce;
	int forceDuration;
	bool active;
	bool done;

public:
	Object(const sf::Texture &text)
	{
		active = false;
		done = false;
		isForceActive = false;
		sprite = new sf::Sprite(text);
		sprite->setOrigin(sprite->getLocalBounds().width / 2.f, sprite->getLocalBounds().height / 2.f);
	}
	virtual void update(); 
	virtual void draw(sf::RenderWindow &window);
	void applyForce(b2Vec2 force, int duration);	
	bool isTargeted(sf::RenderWindow &window);
	void destroy(b2World& world);
	void setColor(sf::Color c = sf::Color::Transparent) { sprite->setColor(c); }
	static sf::Color randColor() { return sf::Color(rand() % 255, rand() % 255, rand() % 255); }

private:
	sf::Vector2f convertCoord(sf::RenderWindow &window);

};
#endif // OBJECT_H