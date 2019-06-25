#pragma once
#include <stdlib.h>
#include <time.h> 
#include "levelTemplates.h"
#include <list>
#include <algorithm>
#include <iostream>

const int tempX = 6;
const int tempY = 6;
const int numBoxGoal = 2;

using namespace std;
class LevelGenerator
{
public:
	LevelGenerator();
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
	bool checkShapeFit(array<array<char, 5>, 5> arr, int m, int n);
	bool canFit(array<array<char, 11>, 11> level, array<array<char, 5>, 5> arr, int startX, int startY, int hight, int width, int size);
	bool contFloor(array<array<char, 11>, 11> level);
	void fillout(int x, int y, int value);
	void addPlayer();
	void addGoals(int numGoals);
	bool checkCorneredBoxes(int x, int y);
	void addBoxes(int numBox);
private:
	array<array<char, 11>, 11> emptyLevel;
	array<array<int, 11>, 11> lev;
	templateShapes* templates;
	array<array<char, 5>, 5> temp;
	int blockPosX = 1;
	int blockPosY = 1;
	int shape = 0;
	int counter = 0;
};
