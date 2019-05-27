#pragma once
#include "levelTemplates.h"
class LevelGenerator
{
public:
	LevelGenerator();
	~LevelGenerator();
	void rotate90(int a[][5], int b[][5], int n, int m);
	void generateLevel(int sizeX, int sizeY);
	void getRandomShape();
	char getGenLevel(int i, int j);
private:
	char emptyLevel[20][20];
	templateShapes templates;
	char temp[5][5];
	int blockPosX = 4;
	int blockPosY = 4;
	int shape = 0;
};

