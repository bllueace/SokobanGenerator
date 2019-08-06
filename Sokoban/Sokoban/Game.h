#ifndef GAME_H
#define GAME_H

#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <string>
#include <iostream>
#include "Level.h"
#include "Solver.h"
#include "TileMap.h"
#include "GameState.h"

using namespace std; 
struct Player
{
	int x;
	int y;
};

class Game : public GameState
{
public:
	Game(StateManager& a_game, sf::Font& font, bool genORno);
	virtual ~Game();
	void pause();
	void resume();
	void event(sf::Time elapsed, sf::Event a_event);
	void update(sf::Time elapsed, int playerInp);
	void draw(VirtualScreen& screen);
	void getSolutionString(string sol);
	void runSolution();
	void initialiseLevel();
	void nextLevel();
	void resetTile(int x, int y);
private:
	sf::Font& font;
	queue<char> solution;
	sf::RenderWindow* window;
	TileMap map;
	Level level;
	Solver solver;
	int numLevel = 1;
	sf::Text playerText;
	std::vector<std::vector<int>> levelData{ 11,std::vector<int>(11,-1) };

	bool pressed= false;
	int set[11][11];
	int numGoals = 0;
	Player playerPos;
	int numtried = 0;

	sf::Text noLevels;
	sf::Text ui[3];

	bool genOrNo;
};

#endif //GAME_H