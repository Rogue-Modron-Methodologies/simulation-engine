#include "StaticObject.h"
#include "DynamicObject.h"
#include <iostream>
#include <vector>
#include <stdlib.h>
#include <ctime>

int main()
{
	std::srand((unsigned)time(NULL));

	sf::RenderWindow window(sf::VideoMode(1000, 1000), "Simulation");
	window.setFramerateLimit(60);

	b2Vec2 gravity(0.f, 10.f);
	b2World world(gravity);

	std::vector<Object> objectList;

	sf::Texture boxTexture;
	boxTexture.loadFromFile("box.png");

	sf::Texture groundTexture;
	groundTexture.loadFromFile("ground.png"); 

	sf::Texture wallTexture;
	wallTexture.loadFromFile("wall.png");

	b2PolygonShape shape;
	shape.SetAsBox((1000.f / 2) / SCALE, (100.f / 2) / SCALE);

	b2FixtureDef groundFixtureDef;
	groundFixtureDef.density = 0.f;
	groundFixtureDef.friction = 0.7f;
	groundFixtureDef.shape = &shape;
	groundFixtureDef.restitution = 1;

	b2BodyDef bodyDef;
	bodyDef.position = b2Vec2(500.f / SCALE, 1000.f / SCALE);
	objectList.push_back(StaticObject(world, bodyDef, groundFixtureDef, groundTexture));

	bodyDef.position = b2Vec2(500.f / SCALE, 0.f / SCALE);
	objectList.push_back(StaticObject(world, bodyDef, groundFixtureDef, groundTexture));

	shape.SetAsBox((100.f / 2) / SCALE, (1000.f / 2) / SCALE);
	groundFixtureDef.shape = &shape;

	bodyDef.position = b2Vec2(1000.f / SCALE, 500.f / SCALE);
	objectList.push_back(StaticObject(world, bodyDef, groundFixtureDef, wallTexture));

	bodyDef.position = b2Vec2(0.f / SCALE, 500.f / SCALE);
	objectList.push_back(StaticObject(world, bodyDef, groundFixtureDef, wallTexture));


	b2FixtureDef boxFixtureDef;
	boxFixtureDef.density = 1.f;
	boxFixtureDef.friction = 0.7f;
	boxFixtureDef.shape = &shape;
	//boxFixtureDef.restitution = 1;

	int randx, randy, randBoxes = rand() % 100;
	for (int i = 0; i < randBoxes; i++)
	{
		randx = rand() % 200 - 100;
		randy = rand() % 200 - 100;
		bodyDef.position = b2Vec2(rand() % window.getSize().x / SCALE, rand() % window.getSize().y / SCALE);
		shape.SetAsBox((32.f / 2) / SCALE, (32.f / 2) / SCALE);
		objectList.push_back(DynamicObject(world, bodyDef, boxFixtureDef, boxTexture));
		objectList.back().applyForce(b2Vec2(randx, randy), 100);

	}

	while (window.isOpen() && randBoxes > 0)
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();
			if (event.type == sf::Event::MouseButtonPressed)
			{
				if (event.mouseButton.button == sf::Mouse::Right)
				{
					int mouseX = sf::Mouse::getPosition(window).x;
					int mouseY = sf::Mouse::getPosition(window).y;

					bodyDef.position = b2Vec2(mouseX / SCALE, mouseY / SCALE);
					shape.SetAsBox((32.f / 2) / SCALE, (32.f / 2) / SCALE);
					objectList.push_back(DynamicObject(world, bodyDef, boxFixtureDef, boxTexture));
				}
				else
				{
					for (std::vector<Object>::iterator it = objectList.begin(); it != objectList.end(); ++it)
					{
						
						if (it->isTargeted(window))
						{
							int randx = rand() % 200 - 100;
							int randy = rand() % 200 - 100;
							it->applyForce(b2Vec2(randx, randy), 100);
							//std::cout << randx << " " << randy << std::endl;
							//it = objectList.erase(it);
							//--randBoxes;
						}
						//else
						//	++it;
					}
					std::cout << randBoxes << std::endl;
				}
			}
		}

		world.Step(1 / 60.f, 8, 3);

		window.clear(sf::Color::White);

		for (std::vector<Object>::iterator it = objectList.begin(); it != objectList.end(); ++it)
		{
			it->update();
			it->draw(window);
		}
		window.display();
	}
	
	return 0;
}


