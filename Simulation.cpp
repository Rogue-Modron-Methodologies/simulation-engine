#include "Simulation.h"

Simulation::Simulation() : txtMngr(), menu(), world(DGRAVITY)
{
	std::srand((unsigned)time(NULL));
	txtMngr.getResource("box.png");
	txtMngr.getResource("ground.png");
	txtMngr.getResource("wall.png");
	name = "Simulation";
}

Simulation::~Simulation() {};

void Simulation::run() {
	int userChoice;
	while (userChoice = loadMainMenu()) {
		switch (userChoice) {
		case 1:
			loadSimulation();
		default:
			break;
		}	
	}
}

int Simulation::loadMainMenu() {
	switch (menu.displayMenu(MAIN_MENU)) {
	case 1: // Run with current options
		return 1;
	case 2: // View current options
		std::cout << "View Current Options HERE\n";
		break;
	case 3: // Change current options
		changeOptions();
		break;
	case 4: // Randomize Options
		std::cout << "RANDOMIZE OPTIONS HERE\n";
		return 1;
	case 5: // Exit
		return 0;
	}
	return 2;
}

void Simulation::changeOptions() {
	int option;
	switch (menu.displayMenu(CURRENT_OPTION_MENU)) {
	case 1: // Simulation Options
		option = menu.displayMenu(SIMULATION_OPTION_MENU);
		changeSimulationOptions(option);
		break;
	case 2: // World Options
		option = menu.displayMenu(WORLD_OPTION_MENU);
		changeWorldOptions(option);
		break;
	case 3: // Object Options
		option = menu.displayMenu(OBJECT_OPTION_MENU);
		changeObjectOptions(option);
		break;
	default: // Exit 
		break;
	}
}

void Simulation::changeSimulationOptions(int userChoice) {
	switch (userChoice) {
	case 1: // Simuation Name
		menu.setStringInput("Simulation Name");
		name = menu.getString();
		break;
	default:
		break;
	}
}

void Simulation::changeWorldOptions(int userChoice) {
	switch (userChoice) {
	case 1: // Gravity
		menu.setParams(-DBL_MAX, DBL_MAX, "Enter Gravity (Horizontal & Vertical)");
		world.SetGravity(b2Vec2((float32)menu.getParam1(), (float32)menu.getParam2()));
		break;
	default:
		break;
	}
}

void Simulation::changeObjectOptions(int userChoice) {
	switch (userChoice) {
	case 1: // Color
		std::cout << "Color Options Here\n";
		break;
	default:
		break;
	}
}

void Simulation::loadSimulation() {
	window = new sf::RenderWindow(sf::VideoMode(1000, 1000), name);
	window->setFramerateLimit(60);

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
		bodyDef.position = b2Vec2(rand() % window->getSize().x / SCALE, rand() % window->getSize().y / SCALE);
		shape.SetAsBox((32.f / 2) / SCALE, (32.f / 2) / SCALE);
		objectList.push_back(DynamicObject(world, bodyDef, boxFixtureDef, txtMngr.getResource(BOX)));
		objectList.back().applyForce(b2Vec2(float32(randx), float32(randy)), 100);
	}

	while (window->isOpen() && randBoxes > 0)
	{
		sf::Event event;
		while (window->pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window->close();
			if (event.type == sf::Event::KeyPressed)
			{
				if (event.key.code == sf::Keyboard::Escape)
					window->close();
			}
			if (event.type == sf::Event::MouseButtonPressed)
			{
				if (event.mouseButton.button == sf::Mouse::Right)
				{
					int mouseX = sf::Mouse::getPosition(*window).x;
					int mouseY = sf::Mouse::getPosition(*window).y;

					bodyDef.position = b2Vec2(mouseX / SCALE, mouseY / SCALE);
					shape.SetAsBox((32.f / 2) / SCALE, (32.f / 2) / SCALE);
					objectList.push_back(DynamicObject(world, bodyDef, boxFixtureDef, txtMngr.getResource(BOX)));
					randBoxes++;
				}
				else
				{
					for (std::vector<Object>::iterator it = objectList.begin(); it != objectList.end(); ++it)
					{

						if (it->isTargeted(*window))
						{
							int randx = rand() % 200 - 100;
							int randy = rand() % 200 - 100;
							it->applyForce(b2Vec2(float32(randx), float32(randy)), 100);
							/*						std::cout << randx << " " << randy << std::endl;
							it = objectList.erase(it);
							--randBoxes;*/
						}
						//else
						//	++it;
					}
					std::cout << randBoxes << std::endl;
				}
			}
		}

		world.Step(1 / 60.f, 8, 3);

		window->clear(sf::Color::White);

		for (std::vector<Object>::iterator it = objectList.begin(); it != objectList.end(); ++it)
		{
			it->update();
			it->draw(*window);
		}
		window->display();
	}

	for (std::vector<Object>::iterator it = objectList.begin(); it != objectList.end(); ++it)
	{
		it->destroy(world);
	}
	objectList.clear();

	delete window;
}