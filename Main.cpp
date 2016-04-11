#include "StaticObject.h"
#include "DynamicObject.h"
#include "ResourceManager.h"
#include <vector>
#include <stdlib.h>
#include <ctime>

const std::string BOX = "box.png";
const std::string GROUND = "ground.png";
const std::string WALL = "wall.png";

bool menu();
void optionMenu();
void loadSimulation(b2World &world, std::vector<Object> &objectList, ResourceManager<sf::Texture> &txtMngr);

int main()
{
	std::srand((unsigned)time(NULL));

	b2Vec2 gravity(0.f, 10.f);
	b2World world(gravity);

	std::vector<Object> objectList;

	ResourceManager<sf::Texture> txtMngr;

	txtMngr.getResource("box.png");
	txtMngr.getResource("ground.png");
	txtMngr.getResource("wall.png");

	while (menu())
		loadSimulation(world, objectList, txtMngr);

	return 0;
}

bool menu()
{
	int response = 0;
	std::cout << "Simulation Options\n";
	std::cout << "1) Run with current options. \n";
	std::cout << "2) View current options. \n";
	std::cout << "3) Change current options. \n";
	std::cout << "4) Randomize Options. \n";
	std::cout << "5) Exit.\n";
	std::cin >> response;
	switch (response)
	{
	case 1:
		return true;
	case 2:
		std::cout << "View Current Options HERE\n";
		break;
	case 3:
		optionMenu();
		break;
	case 4:
		std::cout << "RANDOMIZE OPTIONS HERE\n";
		return true;
	case 5:
		return false;
	}
}

void optionMenu()
{
	int response = 0;
	std::cout << "Options Menu\n";
	std::cout << "1) Gravity Options\n";
	//std::cout << "2) \n";
	//std::cout << "3) \n";
	//std::cout << "4) \n";
	//std::cout << "5) \n";
	//std::cout << "6) \n";
	//std::cout << "7) \n";
	//std::cout << "8) \n";
	std::cout << "9) Exit with no changes. \n";
	std::cin >> response;
	switch (response)
	{
	case 1:
		std::cout << "Gravity Change Here\n";
	default:
		std::cout << "Rerunning Simulation with current options\n";
		break;
	}
}

void loadSimulation(b2World &world, std::vector<Object> &objectList, ResourceManager<sf::Texture> &txtMngr)
{
	sf::RenderWindow window(sf::VideoMode(1000, 1000), "Simulation");
	window.setFramerateLimit(60);

	b2PolygonShape shape;
	shape.SetAsBox((1000.f / 2) / SCALE, (100.f / 2) / SCALE);

	b2FixtureDef groundFixtureDef;
	groundFixtureDef.density = 0.f;
	groundFixtureDef.friction = 0.7f;
	groundFixtureDef.shape = &shape;
	groundFixtureDef.restitution = 1;

	b2BodyDef bodyDef;
	bodyDef.position = b2Vec2(500.f / SCALE, 1000.f / SCALE);
	objectList.push_back(StaticObject(world, bodyDef, groundFixtureDef, txtMngr.getResource(GROUND)));

	bodyDef.position = b2Vec2(500.f / SCALE, 0.f / SCALE);
	objectList.push_back(StaticObject(world, bodyDef, groundFixtureDef, txtMngr.getResource(GROUND)));

	shape.SetAsBox((100.f / 2) / SCALE, (1000.f / 2) / SCALE);
	groundFixtureDef.shape = &shape;

	bodyDef.position = b2Vec2(1000.f / SCALE, 500.f / SCALE);
	objectList.push_back(StaticObject(world, bodyDef, groundFixtureDef, txtMngr.getResource(WALL)));

	bodyDef.position = b2Vec2(0.f / SCALE, 500.f / SCALE);
	objectList.push_back(StaticObject(world, bodyDef, groundFixtureDef, txtMngr.getResource(WALL)));


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
		objectList.push_back(DynamicObject(world, bodyDef, boxFixtureDef, txtMngr.getResource(BOX)));
		objectList.back().applyForce(b2Vec2(float32(randx), float32(randy)), 100);
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
					objectList.push_back(DynamicObject(world, bodyDef, boxFixtureDef, txtMngr.getResource(BOX)));
					randBoxes++;
				}
				else
				{
					for (std::vector<Object>::iterator it = objectList.begin(); it != objectList.end(); ++it)
					{

						if (it->isTargeted(window))
						{
							int randx = rand() % 200 - 100;
							int randy = rand() % 200 - 100;
							it->applyForce(b2Vec2(float32(randx), float32(randy)), 100);
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

	for (std::vector<Object>::iterator it = objectList.begin(); it != objectList.end(); ++it)
	{
		it->destroy(world);
	}
	objectList.clear();
}
