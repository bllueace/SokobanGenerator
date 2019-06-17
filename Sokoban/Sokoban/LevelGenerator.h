#pragma once
#include <stdlib.h>     /* srand, rand */
#include <time.h>       /* time */
#include "levelTemplates.h"
#include <list>
#include <algorithm>
#include <iostream>
using namespace std;
class LevelGenerator
{
public:
	LevelGenerator();
	~LevelGenerator();
	void rotate90(char arr[][5]);
	void flipShapeR(char arr[][5]);
	void flipShapeU(char arr[][5]);
	void generateLevel(int height, int width);
	void getRandomShape();
	char getGenLevel(int i, int j);
	bool checkShapeFit(char a[][5], int m, int n);
	bool canFit(char level[][20], char piece[][5], int startX, int startY, int hight, int width, int size);
private:
	char emptyLevel[20][20];
	templateShapes templates;
	char temp[5][5];
	//char temp2[5][5];
	int blockPosX = 0;
	int blockPosY = 0;
	int shape = 0;
};
