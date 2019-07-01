#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
//#include <Windows.h>
#include <string>
#include <iostream>
#include <queue>
#include <tuple>
#include <array>
#include "Input.h"
#include "States.h"
#include "Level.h"
#include "Solver.h"
#include "TileMap.h"
using namespace std;

struct Player
{
	int x;
	int y;
};

class Game
{
public:

	void getSolutionString(string sol);
	void runSolution();
	void handleInput();
	void initialiseLevel();
	void resetTile(int x, int y);
	void update(int playerMove);
	GameState getState();
	void render();
	void beginDraw();
	void endDraw();
	Game(sf::RenderWindow* hwnd, Input* in);
	~Game();
private:
	sf::Font font;
	queue<char> solution;
	sf::RenderWindow* window;
	GameState state;
	Input* input;
	TileMap map;
	Level level;
	Solver solver;
	int playerInp = 99;
	sf::Text playerText;
	std::vector<std::vector<int>> levelData{ 11,std::vector<int>(11,-1) };

	bool pressed= false;
	sf::Event event;
	int set[11][11];
	int numGoals = 0;
	Player playerPos;
};

