#include "LevelGenerator.h"
#include <stdlib.h>
#include <vcruntime_string.h>
#include <xutility>

LevelGenerator::LevelGenerator()
{
	for (int i = 0; i < 20; i++)
	{
		for (int j = 0; j < 20; j++)
		{
			emptyLevel[i][j] = '#';
		}
	}

	//for (int i = 0; i < 5; i++)
	//{
	//	for (int j = 0; j < 5; j++)
	//	{
	//		emptyLevel[i+5][j+5] = templates.shape9[i][j];
	//	}
	//}

	generateLevel(2, 2);

}

LevelGenerator::~LevelGenerator()
{
}

void LevelGenerator::rotate90(int a[][5], int b[][5], int n, int m)
{
	for (int i = 0; i < n; i++)
		for (int j = 0; j < m; j++)
			b[i][j] = a[n - j - 1][i];
}

void LevelGenerator::generateLevel(int sizeX, int sizeY)
{
	getRandomShape();

	for (int i = 0; i < sizeX; i++)
	{
		for (int j = 0; j < sizeY; j++)
		{
			//getRandomShape();

			for (int k = 0; k < 5; k++)
			{
				for (int p = 0; p < 5; p++)
				{
					emptyLevel[k + blockPosX][p + blockPosY] = templates.shape10[k][p];
					//emptyLevel[k + blockPosX][p + blockPosY] == temp[k][p];
				}
			}
			blockPosY += 4;
		}
		blockPosY = 4;
		blockPosX += 4;
	}
}

void LevelGenerator::getRandomShape()
{
	//shape = rand() % 17+1;
	shape = 0;
	switch (shape)
	{
	case 0:
		//temp == templates.shape1;
		//memcpy(temp, templates.shape4, sizeof temp);
		memcpy(temp, templates.shape11,sizeof *templates.shape11);
		//std::copy_n(templates.shape4, 25, temp);
		break;
	case 1:
		//temp == templates.shape2;
		//memcpy(temp , templates.shape4, sizeof temp);
		break;
	case 2:
		temp == templates.shape3;
		break;
	case 3:
		temp == templates.shape4;
		break;
	case 4:
		temp == templates.shape5;
		break;
	case 5:
		temp == templates.shape6;
		break;
	case 6:
		temp == templates.shape7;
		break;
	case 7:
		temp == templates.shape8;
		break;
	case 8:
		temp == templates.shape9;
		break;
	case 9:
		temp == templates.shape10;
		break;
	case 10:
		temp == templates.shape11;
		break;
	case 11:
		temp == templates.shape12;
		break;
	case 12:
		temp == templates.shape13;
		break;
	case 13:
		temp == templates.shape14;
		break;
	case 14:
		temp == templates.shape15;
		break;
	case 15:
		temp == templates.shape16;
		break;
	case 16:
		temp == templates.shape17;
		break;
	}

}

char LevelGenerator::getGenLevel(int i,int j)
{
	//generateLevel(2, 2);

	return emptyLevel[i][j];
}
