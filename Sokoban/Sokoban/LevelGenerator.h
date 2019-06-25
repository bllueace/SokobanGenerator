#pragma once
#include <stdlib.h>
#include <time.h> 
#include "levelTemplates.h"
#include <list>
#include <algorithm>
#include <iostream>

const int tempX = 9;
const int tempY = 9;
const int numBoxGoal = 3;

using namespace std;
class LevelGenerator
{
public:
	LevelGenerator();
	~LevelGenerator();
	void makeLevel();
	int random(int min, int max);
	void print(array<array<char, 20>, 20> level);
	void rotate90(array<array<char, 5>, 5> arr);
	void flipShapeR(array<array<char, 5>, 5> arr);
	void flipShapeU(array<array<char, 5>, 5> arr);
	void generateLevel(int height, int width);
	void getRandomShape();
	char getGenLevel(int i, int j);
	bool checkShapeFit(array<array<char, 5>, 5> arr, int m, int n);
	bool canFit(array<array<char, 20>, 20> level, array<array<char, 5>, 5> arr, int startX, int startY, int hight, int width, int size);
	bool contFloor(array<array<char, 20>, 20> level);
	bool contFloor2(array<array<char, 20>, 20> level);
	void fillout(int x, int y, int value);
	void addPlayer();
	void addGoals(int numGoals);
	void addBoxes(int numBox);
private:
	array<array<char, 20>, 20> emptyLevel;
	array<array<int, 20>, 20> lev;
	templateShapes* templates;
	array<array<char, 5>, 5> temp;
	int blockPosX = 1;
	int blockPosY = 1;
	int shape = 0;
	int counter = 0;
};
