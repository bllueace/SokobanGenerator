#include <fstream>
#include <iomanip>
#include <iostream>
#include <vector>
#include "Level.h"

using namespace std;

Level::Level()
{	
}

void Level::initialize(int level) 
{
	//if (level != 99)
	//{
	//	int i = 0, j = 0, t;
	//	ifstream ip;
	//	ip.open("levels/" + to_string(level) + ".txt");
	//	if (ip.fail())
	//	{
	//		cerr << "Error opening level #" << level << ". Check if file is corrupted\n";
	//	}
	//	ip >> t;
	//	push = t;
	//	char z;
	//	ip.get(z);
	//	if (z == '\n')
	//	{
	//		ip.get(z);
	//		for (int i = 0; i < XWIDE; i++)
	//		{
	//			if (z == '\n')
	//			{
	//				ip.get(z);
	//			}
	//			for (int j = 0; j < YWIDE; j++)
	//			{
	//				switch (z)
	//				{
	//				case '#': //walls
	//					gridVal[i][j] = 1;
	//					break;
	//				case '$': //Box
	//					gridVal[i][j] = 2;
	//					break;
	//				case '.': //Goal
	//					gridVal[i][j] = 3;
	//					break;
	//				case '@': //Player
	//					gridVal[i][j] = 4;
	//					break;
	//				case '?': //Box on goal
	//					gridVal[i][j] = 5;
	//					break;
	//				case '+': //Player on goal
	//					gridVal[i][j] = 6;
	//					break;
	//				case ' ': //Empty
	//					gridVal[i][j] = 0;
	//					break;
	//				case '*':
	//					gridVal[i][j] = 0; // outside environment
	//					break;
	//				}
	//				ip.get(z);
	//				if (z == '\n')
	//				{
	//					ip.get(z);
	//				}
	//			}
	//		}
	//	}
	//	initalized = true;
	//	ip.close();
	//}

	//if (level == 99)
	//{
		testLevel = new LevelGenerator;
		testLevel->makeLevel();
		for (int i = 0; i < XWIDE; i++)
		{
			for (int j = 0; j < YWIDE; j++)
			{
				switch (testLevel->getGenLevel(i,j))
				{
				case '#': //walls
					gridVal[i][j] = 1;
					break;
				case '$': //Box
					gridVal[i][j] = 2;
					break;
				case '.': //Goal
					gridVal[i][j] = 3;
					break;
				case '@': //Player
					gridVal[i][j] = 4;
					break;
				case '?': //Box on goal
					gridVal[i][j] = 5;
					break;
				case '+': //Player on goal
					gridVal[i][j] = 6;
					break;
				case ' ': //Empty
					gridVal[i][j] = 0;
					break;
				case '0':
					gridVal[i][j] = 1; // outside environment
					break;
				}
			}
		}
	//}
}

int Level::getContent(int i, int j) {
	return gridVal[i][j];
}

void Level::print() {
	for (int i = 0; i < XWIDE; i++) {
		for (int j = 0; j < YWIDE; j++) {
			cout << setw(2);
			cout << gridVal[i][j] << " ";
		}
		cout << endl;
	}
}

int Level::getPush() {
	return push;
}

void Level::empty() {
	for (int i = 0; i < YWIDE; i++) {
		for (int j = 0; j < XWIDE; j++) {
			gridVal[i][j] = -1;
		}
	}
}