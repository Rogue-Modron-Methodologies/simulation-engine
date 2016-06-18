#include "Simulation.h"

Simulation::Simulation() : txtMngr(), menu(), world(DGRAVITY) {
	std::srand((unsigned)time(NULL));
	txtMngr.getResource("box.png");
	txtMngr.getResource("ground.png");
	txtMngr.getResource("wall.png");
	simOptions.name = "Simulation";
	simOptions.gravity = DGRAVITY;
	foreObjOptions.quantity = 100;
	foreObjOptions.color = sf::Color::Black;
	foreObjOptions.sfShape = Shape::square;
	foreObjOptions.dimension = b2Vec2(32.0 / 2, 32.0 / 2);
}

Simulation::~Simulation() {};

void Simulation::run() {
	int userChoice;
	while (userChoice = menu.displayMenu(MAIN_MENU)) {
		switch (userChoice) {
		case 1: // Run with current options
			loadSimulation();
			runSimulation();
		case 2: // View current options
			displayCurrentOptions();
			break;
		case 3: // Change current options
			changeOptions();
			break;
		case 4: // Randomize Options
			randomizeOptions();	
			break;
		default:
			return;
		}	
	}
}

void Simulation::changeOptions() {
	int option;
	switch (menu.displayMenu(CURRENT_OPTION_MENU)) {
	case 1: // Simulation Options
		option = menu.displayMenu(SIMULATION_OPTION_MENU);
		changeSimulationOptions(option);
		break;
	case 2: // Object Options
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
		simOptions.name = menu.getString();
		break;
	case 2: // Gravity
		menu.setParams(-DBL_MAX, DBL_MAX, "Enter Gravity (Horizontal & Vertical)");
		simOptions.gravity = b2Vec2((float32)menu.getParam1(), (float32)menu.getParam2());
		break;
	default:
		break;
	}
}


void Simulation::changeObjectOptions(int userChoice) {
	int choice;
	switch (userChoice) {
	case 1: // Quantity
		std::cout << "How Many Objects?\n";
		cin >> foreObjOptions.quantity;
		break;
	case 2: // Dimensions
		cout << "Enter Dimension\n";
		cin >> foreObjOptions.dimension.x;
		foreObjOptions.dimension.y = foreObjOptions.dimension.x;
		break;
	case 3: // Shape
		choice = menu.displayMenu(SHAPE_LIST);
		switch (Shape(choice - 1)) {
		case Shape::circle:
			std::cout << "Circle\n";
			break;
		case Shape::square:
			std::cout << "Square\n";
			break;
		case Shape::rectangle:
			std::cout << "Rectangle\n";
			break;
		case Shape::triangle:
			std::cout << "Triangle\n";
			break;
		default:
			break;
		}
		break;
	case 4: // Color
		choice = menu.displayMenu(COLOR_LIST);
		switch (choice)
		{
		case 1:
			foreObjOptions.color = sf::Color::Red;
			break;
		case 2:
			foreObjOptions.color = sf::Color::Green;
			break;
		case 3:
			foreObjOptions.color = sf::Color::Blue;
			break;
		case 4:
			foreObjOptions.color = sf::Color::Transparent;
			break;
		default:
			foreObjOptions.color = Object::randColor();
			break;
		}
		break;
	case 5: // Density
		std::cout << "Density\n";
		cin >> foreObjOptions.fixtDef.density;
		break;
	case 6: // Friction
		std::cout << "Friction \n";
		cin >> foreObjOptions.fixtDef.friction;
		break;
	case 7: // Restitution
		std::cout << "Resitution\n";
		cin >> foreObjOptions.fixtDef.restitution;
		break;
	default:
		break;
	}
}

void Simulation::randomizeOptions() {
	simOptions.name = "Random Simulation";
	float32 x = static_cast<float32>(rand() % 80 - 40);
	float32 y = static_cast<float32>(rand() % 80 - 40);
	simOptions.gravity = b2Vec2(x, y);
	foreObjOptions.quantity = rand() % 100;
	foreObjOptions.color = Object::randColor();
	foreObjOptions.fixtDef.density = (float32)(rand() % 5 + 1);
	foreObjOptions.fixtDef.friction = (float32)((rand() % 100 + 1) / 100.0);
	foreObjOptions.fixtDef.restitution = (float32)((rand() % 100 + 1) / 100.0);
	foreObjOptions.dimension.x = rand() % 50 + 10.0f;
	foreObjOptions.dimension.y = rand() % 50 + 10.0f;

}

void Simulation::loadSimulation() {
	window = new sf::RenderWindow(sf::VideoMode(1000, 1000), simOptions.name);
	window->setFramerateLimit(60);
	world.SetGravity(simOptions.gravity);

	loadEnviornment();
	loadObjectList();
}

void Simulation::loadEnviornment() {

	b2PolygonShape shape;
	shape.SetAsBox((1000.f / 2) / SCALE, (100.f / 2) / SCALE);
	b2FixtureDef groundFixtureDef;
	groundFixtureDef.density = 0.f;
	groundFixtureDef.friction = 0.5f;
	groundFixtureDef.shape = &shape;
	groundFixtureDef.restitution = 0.5f;

	b2BodyDef bodyDef;
	bodyDef.position = b2Vec2(500.f / SCALE, 1000.f / SCALE);
	objectList.push_back(StaticObject(world, bodyDef, groundFixtureDef));

	bodyDef.position = b2Vec2(500.f / SCALE, 0.f / SCALE);
	objectList.push_back(StaticObject(world, bodyDef, groundFixtureDef));

	shape.SetAsBox((100.f / 2) / SCALE, (1000.f / 2) / SCALE);
	groundFixtureDef.shape = &shape;

	bodyDef.position = b2Vec2(1000.f / SCALE, 500.f / SCALE);
	objectList.push_back(StaticObject(world, bodyDef, groundFixtureDef));

	bodyDef.position = b2Vec2(0.f / SCALE, 500.f / SCALE);
	objectList.push_back(StaticObject(world, bodyDef, groundFixtureDef));
}

void Simulation::loadObjectList() {
	for (int i = 0; i < foreObjOptions.quantity; i++) {
		foreObjOptions.position = b2Vec2(rand() % window->getSize().x / SCALE, rand() % window->getSize().y / SCALE);
		objectList.push_back(DynamicObject(world, window, foreObjOptions));
		objectList.back().applyForce(b2Vec2(float32(rand() % 200 - 100), float32(rand() % 200 - 100)), 100);
	}
}

void Simulation::displayCurrentOptions() {
	std::cout << left;
	std::cout << setw(20) << "Simulation Options:\n";
	std::cout << setw(20) << "Simulation Name:" << simOptions.name << std::endl;
	std::cout << setw(20) << "Gravity:" << "X: " << simOptions.gravity.x << "  Y: " << simOptions.gravity.y << std::endl << std::endl;
	std::cout << setw(20) << "Foreground Objects:\n";
	std::cout << setw(20) << "Quantity:" << foreObjOptions.quantity << std::endl;
	std::cout << setw(20) << "Dimensions:" << "X: " << foreObjOptions.dimension.x << "  Y: " << foreObjOptions.dimension.y << std::endl;
	std::cout << setw(20) << "Color:" << foreObjOptions.color.toInteger() << std::endl;
	std::cout << setw(20) << "Density:" << foreObjOptions.fixtDef.density << std::endl;
	std::cout << setw(20) << "Restitution:" << foreObjOptions.fixtDef.restitution << std::endl;
	std::cout << setw(20) << "Friction:" << foreObjOptions.fixtDef.friction << std::endl << std::endl;

	cout << std::endl;
}

void Simulation::runSimulation() {
	displayCurrentOptions();
	while (window->isOpen()) {
		sf::Event event;
		while (window->pollEvent(event)) {
			if (event.type == sf::Event::Closed)
				window->close();
			if (event.type == sf::Event::KeyPressed) {
				if (event.key.code == sf::Keyboard::Escape)
					window->close();
			}
			if (event.type == sf::Event::MouseButtonPressed)
			{
				if (event.mouseButton.button == sf::Mouse::Right)
				{
					//int mouseX = sf::Mouse::getPosition(*window).x;
					//int mouseY = sf::Mouse::getPosition(*window).y;
					//bodyDef.position = b2Vec2(mouseX / SCALE, mouseY / SCALE);
					//shape.SetAsBox((32.f / 2) / SCALE, (32.f / 2) / SCALE);
					//objectList.push_back(DynamicObject(world, bodyDef, boxFixtureDef, txtMngr.getResource(BOX)));
					//randBoxes++;
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
				}
			}
		}

		world.Step(1 / 60.f, 8, 3);

		window->clear(sf::Color::White);

		for (std::vector<Object>::iterator it = objectList.begin(); it != objectList.end(); ++it) {
			it->update();
			it->draw(*window);
		}
		window->display();
	}

	for (std::vector<Object>::iterator it = objectList.begin(); it != objectList.end(); ++it)
		it->destroy(world);
	objectList.clear();
	delete window;
}

