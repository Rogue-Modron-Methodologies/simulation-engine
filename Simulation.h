#ifndef SIMULATION_H
#define SIMULATION_H

#include "StaticObject.h"
#include "DynamicObject.h"
#include "ResourceManager.h"
#include "ConsoleMenu.h"
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
	"Simulation Name" };
const std::vector<string> WORLD_OPTION_MENU = {
	"Gravity Option" };
const std::vector<string> OBJECT_OPTION_MENU = {
	"Quantity",
	"Dimensions",
	"Shape",
	"Color",
	"Density",
	"Friction",
	"Resitution" };
const std::vector<string> COLOR_LIST = {
	"Red",
	"Green",
	"Blue",
	"None",
	"Random" };
const std::vector<string> SHAPE_LIST = {
	"Circle",
	"Rectangle",
	"Square",
	"Triangle" };
const b2Vec2 DGRAVITY(0.f, 10.f);
const std::string BOX = "box.png";
const std::string GROUND = "ground.png";
const std::string WALL = "wall.png";



class Simulation {
	ResourceManager<sf::Texture> txtMngr;
	sf::RenderWindow *window;
	std::vector<Object> objectList;
	Options cOptions;
	b2World world;
	ConsoleMenu menu;

public:
	Simulation();
	~Simulation();
	void run();

private:
	void runSimulation();
	void loadSimulation();
	void randomizeOptions();
	void loadEnviornment();
	void loadObjectList();
	int loadMainMenu();
	void changeOptions(); 
	void changeSimulationOptions(int userChoice);
	void changeWorldOptions(int userChoice);
	void changeObjectOptions(int userChoice);
	void displayCurrentOptions();
}; 
#endif // SIMULATION_H
