#ifndef LEVEL_H
#define LEVEL_H


#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <windows.h>
#include <string>
#include <memory>
#include <iostream>
#include <list>

#include "LevelGenerator.h"

class Level
{
public:
	Level();
	void initialize(int);
	bool initalized = false;
	int getContent(int i, int j);
	void print();
	int getPush();
	void empty();
private:
	std::vector<std::vector<int>> gridVal{ 11,std::vector<int>(11,-1)};
	sf::RenderWindow* window;

	int push;
	const int XWIDE = 11;
	const int YWIDE = 11;
	array<array<int, 11>, 11> lev;

	LevelGenerator *generatedLevel;
};
#endif //LEVEL_H