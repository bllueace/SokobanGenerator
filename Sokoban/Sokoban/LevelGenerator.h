#ifndef LEVELGENERATOR_H
#define LEVELGENERATOR_H

#include "Solver.h"

#include <stdlib.h>
#include <time.h> 
#include "levelTemplates.h"
#include <list>
#include <algorithm>
#include <fstream>      // std::ofstream
#include <iosfwd>
#include <vector>
#include <chrono>
#include <condition_variable>
#include "GameState.h"
#include "Menu.h"

using std::chrono::duration_cast;
using std::chrono::milliseconds;
typedef std::chrono::steady_clock the_clock;

using namespace std;
#define placementCheck 10
#define MAX_NUMBER 6
//const int tempX = 9;
//const int tempY = 9;
//const int numBoxGoal = 2;

class LevelGenerator :public GameState
{
public:
	LevelGenerator(StateManager& a_game, sf::Font& a_font);
	~LevelGenerator();
	void makeLevel();
	int random(int min, int max);
	void print(array<array<char, 11>, 11> level);
	void rotate90(array<array<char, 5>, 5> arr);
	void flipShapeR(array<array<char, 5>, 5> arr);
	void flipShapeU(array<array<char, 5>, 5> arr);
	void generateLevel(int height, int width);
	void getRandomShape();
	char getGenLevel(int i, int j);
	bool canFit(array<array<char, 11>, 11> level, array<array<char, 5>, 5> arr, int startX, int startY, int hight, int width, int size);
	bool contFloor(array<array<char, 11>, 11> level);
	void fillout(int x, int y, int value);
	void addPlayer();
	void addGoals(int numGoals);
	bool checkCorneredBoxes(int x, int y);
	void addBoxes(int numBox);
	void saveGenLevels();

	void event(sf::Time elapsed, sf::Event a_event);
	void update(sf::Time elapsed, int playerInp);
	void draw(VirtualScreen& screen);
	void pause();
	void resume();
	void prepareLevelForSolver();
	void MoveUp();
	void MoveDown();
	int getPressedItem() { return selectedItem; }

private:
	array<array<char, 11>, 11> emptyLevel;
	array<array<int, 11>, 11> lev;
	templateShapes* templates;
	array<array<char, 5>, 5> temp;
	int blockPosX = 1;
	int blockPosY = 1;
	int shape = 0;
	int counter = 0;

	int num = 1;

private:
	std::vector<std::vector<int>> numericalLevel{ 11,std::vector<int>(11,-1) };

	sf::Font& font;
	sf::RectangleShape bgr1;
	sf::Texture menuBackground1;
	Solver solver;

	string solution;

	int time_taken;
	int selectedItem;
	sf::Text menu[MAX_NUMBER];
	int numLevels = 3;
	int numBoxGoal = 2;
	int tempY = 3;
	int tempX = 6;
};

#endif //LEVELGENERATOR_H
