#ifndef SIMULATION_H
#define SIMULATION_H

#include "StaticObject.h"
#include "DynamicObject.h"
#include "ResourceManager.h"
#include "ConsoleMenu.h"
#include "SFMLDebugDraw.h"
#include <vector>
#include <stdlib.h>
#include <ctime>

const bool DEBUG = false;		// toggle debug draw

const std::vector<string> MAIN_MENU = { 
	"Run with current options.",
	"View current options.",
	"Change current options.",
	"Randomize Options." };
const std::vector<string> CURRENT_OPTION_MENU = {
	"Simulation Options",
	"Object Options" };
const std::vector<string> SIMULATION_OPTION_MENU = {
	"Simulation Name", 
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

struct simTemplate {
	std::string name;
	b2Vec2 gravity;
};

class Simulation {
	ResourceManager<sf::Texture> txtMngr;
	sf::RenderWindow *window;
	std::vector<Object> objectList;
	simTemplate simOptions;
	objTemplate foreObjOptions;
	objTemplate backObjOptions;
	b2World world;
	ConsoleMenu menu;
	SFMLDebugDraw *dbDraw;

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
	void loadWalls(bool left = true, bool top = true, bool right = true, bool bottom = true);
	int loadMainMenu();
	void changeOptions(); 
	void changeSimulationOptions(int userChoice);
	void changeObjectOptions(int userChoice);
	void displayCurrentOptions();
}; 
#endif // SIMULATION_H
