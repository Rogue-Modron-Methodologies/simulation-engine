#ifndef SIMULATION_H
#define SIMULATION_H

#include "StaticObject.h"
#include "DynamicObject.h"
#include "ResourceManager.h"
#include "Menu.h"
#include <vector>
#include <stdlib.h>
#include <ctime>

const b2Vec2 DGRAVITY(0.f, 10.f);
const std::string BOX = "box.png";
const std::string GROUND = "ground.png";
const std::string WALL = "wall.png";

class Simulation {

	ResourceManager<sf::Texture> txtMngr;
	std::vector<Object> objectList;
	b2World world;
	Menu menu;

public:
	Simulation();
	~Simulation();
	void run();

private:
	void loadSimulation();
	bool loadMainMenu();
	void changeSimulationOptions(int userChoice);
};

#endif // SIMULATION_H