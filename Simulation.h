#ifndef SIMULATION_H
#define SIMULATION_H

#include "StaticObject.h"
#include "DynamicObject.h"
#include "ResourceManager.h"
#include "Menu.h"
#include <vector>
#include <stdlib.h>
#include <ctime>

const std::vector<string> MAIN_MENU = { 
	"Run with current options.",
	"View current options.",
	"Change current options.",
	"Randomize Options." };
const std::vector<string> CURRENT_OPTION_MENU = {
	"Simulation Options",
	"World Options",
	"Object Options" };

const std::vector<string> SIMULATION_OPTION_MENU = {
	"Mouse Click Options" };

const std::vector<string> WORLD_OPTION_MENU = {
	"Gravity Option" };

const std::vector<string> OBJECT_OPTION_MENU = {
	"Color Options" };

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
	int loadMainMenu();
	void changeOptions(); 
	void changeSimulationOptions(int userChoice);
	void changeWorldOptions(int userChoice);
	void changeObjectOptions(int userChoice);
}; 
#endif // SIMULATION_H
