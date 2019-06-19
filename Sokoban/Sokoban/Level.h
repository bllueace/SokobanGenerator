#pragma once
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
	std::vector<std::vector<int>> gridVal{ 20,std::vector<int>(20,-1)};
	sf::RenderWindow* window;

	int push;
	const int XWIDE = 20;
	const int YWIDE = 20;

	LevelGenerator *testLevel;
};

