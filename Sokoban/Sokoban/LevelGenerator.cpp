#include "LevelGenerator.h"
#include <vcruntime_string.h>
#include <xutility>
#include <queue>

LevelGenerator::LevelGenerator()
{
	srand(time(NULL));
	//initialize the entire array
	for (int i = 0; i < 20; i++)
	{
		for (int j = 0; j < 20; j++)
		{
			emptyLevel[i][j] = '0';
		}
	}
	//set generated level size
	generateLevel(6,6);
}

LevelGenerator::~LevelGenerator()
{
}
//rotates an 2d array 
void LevelGenerator::rotate90(char arr[][5])
{
	char result[5][5];
	for (int i = 0; i < 5; i++)
		for (int j = 0; j < 5; j++)
			result[i][j] = arr[5 - j - 1][i];

	memcpy(temp, result, sizeof temp);
}
//flip the array up
void LevelGenerator::flipShapeU(char arr[][5])
{
	char result[5][5];
	for (int i = 0; i < 5; i++)
		for (int y = 0; y < 5; y++)
			result[i][y] = arr[5 - i - 1][y];

	memcpy(temp, result, sizeof temp);
}
//flip the array right
void LevelGenerator::flipShapeR(char arr[][5])
{
	char result[5][5];
	for (int i = 0; i < 5; i++)
		for (int y = 0; y < 5; y++)
			result[i][y] = arr[i][5 - y - 1];

	memcpy(temp, result, sizeof temp);
}

void LevelGenerator::generateLevel(int height, int width)
{
	int count = 0;
	while (true)
	{
		getRandomShape();

		if (canFit(emptyLevel, temp, blockPosX, blockPosY, height, width, 5))
		{
			for (int k = 0; k < 3; k++)
			{
				for (int p = 0; p < 3; p++)
				{
					if (blockPosX + k < 20 && blockPosY + p < 20)
					{
						emptyLevel[blockPosX + k][blockPosY + p] = temp[k+1][p+1];
					}

					//if (temp[k][p] != '0')
						//emptyLevel[k + blockPosX][p + blockPosY] = temp[k+1][p+1];
				}
			}

			blockPosX += 3;
			if (blockPosX > height - 1)
			{
				blockPosY += 3;
				blockPosX = 0;
			}
		}
		if (blockPosY > width - 1)
			return;

		count++;
		if (count > 1000000)
		return;
	}
}

void LevelGenerator::getRandomShape()
{
	shape = rand() % 17 + 1;
	//shape = 17;
	//choose x shape
	switch (shape)
	{
	case 1:
		memcpy(temp, templates.shape1, sizeof templates.shape1);
		break;
	case 2:
		memcpy(temp, templates.shape2, sizeof templates.shape2);
		break;
	case 3:
		memcpy(temp, templates.shape3, sizeof templates.shape3);
		break;
	case 4:
		memcpy(temp, templates.shape4, sizeof templates.shape4);
		break;
	case 5:
		memcpy(temp, templates.shape5, sizeof templates.shape5);
		break;
	case 6:
		memcpy(temp, templates.shape6, sizeof templates.shape6);
		break;
	case 7:
		memcpy(temp, templates.shape7, sizeof templates.shape7);
		break;
	case 8:
		memcpy(temp, templates.shape8, sizeof templates.shape8);
		break;
	case 9:
		memcpy(temp, templates.shape9, sizeof templates.shape9);
		break;
	case 10:
		memcpy(temp, templates.shape10, sizeof templates.shape10);
		break;
	case 11:
		memcpy(temp, templates.shape11, sizeof templates.shape11);
		break;
	case 12:
		memcpy(temp, templates.shape12, sizeof templates.shape12);
		break;
	case 13:
		memcpy(temp, templates.shape13, sizeof templates.shape13);
		break;
	case 14:
		memcpy(temp, templates.shape14, sizeof templates.shape14);
		break;
	case 15:
		memcpy(temp, templates.shape15, sizeof templates.shape15);
		break;
	case 16:
		memcpy(temp, templates.shape16, sizeof templates.shape16);
		break;
	case 17:
		memcpy(temp, templates.shape17, sizeof templates.shape17);
		break;
	}

	//rotate x times
	int rnd = rand() % 3 + 1;
	for (int r = 0; r < rnd; r++)
	{
		rotate90(temp);
	}
	//flip x direction
	rnd = rand() % 3;
	if (rnd == 1)
	{
		flipShapeR(temp);
	}
	else if (rnd == 2)
	{
		flipShapeU(temp);
	}
}

char LevelGenerator::getGenLevel(int i,int j)
{
	//if (contFloor(emptyLevel))
	//{
	//	return emptyLevel[i][j];
	//}
	return emptyLevel[i][j];

}

bool LevelGenerator::checkShapeFit(char a[][5], int m, int n)
{
	list<int> x;
	list<int> y;
	for (int i = 0; i < m; i++) {
		for (int j = 0; j < n; j++) {
			if ((i == 0 || j == 0 || i == n - 1 || j == n - 1) && (a[i][j] == ' '))
			{
				x.push_front(i);
				y.push_front(j);
				cout << "Indices are : " << i << ":" << j << endl;
			}
		}
	}
	return true;
}

bool LevelGenerator::canFit(char level[][20], char piece[][5], int startX, int startY, int hight, int width, int size)
{
	bool fit = true;
	//check top
	for (int i = 0; i < size; i++)
	{
		if (startY + i < width)
		{
			if (level[startX][startY + i] != ' ')
			{
				if (level[startX][startY + i] != piece[0][i])
				{
					fit = false;
				}
			}
		}
	}
	//check left
	for (int i = 0; i < size; i++)
	{
		if (startX + i < hight)
		{
			if (level[startX + i][startY] != ' ')
			{
				if (level[startX + i][startY] != piece[i][0])
				{
					fit = false;
				}
			}
		}
	}
	//check right
	for (int i = 0; i < size; i++)
	{
		if (startX + 4 < hight)
		{
			if (startY + i < width)
			{
				if (level[startX + 4][startY+i] != ' ')
				{
					if (level[startX + 4][startY+i] != piece[4][i])
					{
						fit = false;
					}
				}
			}
		}
	}
	//check bottom
	for (int i = 0; i < size; i++)
	{
		if (startY + 4 < width)
		{
			if (startX + i < hight)
			{
				if (level[startX + i][startY + 4] != ' ')
				{
					if (level[startX + i][startY + 4] != piece[i][4])
					{
						fit = false;
					}
				}
			}
		}
	}
	return fit;
}

bool LevelGenerator::contFloor(char level[][20])
{
	bool valid = true;
	queue<int> xp;
	queue<int> yp;
	queue<queue<int>> que;
	int count = 1;

	int test[6][6];

	for (int i = 0; i < 6; i++)
	{
		for (int j = 0; j < 6; j++)
		{
			test[i][j] = 0;
		}
	}

	for (int x = 0; x < 6; x++)
	{
		for (int y = 0; y < 6; y++)
		{
			if (level[x][y] == '#')
			{
				if (test[x][y] == 0)
				{
					xp.push(x);
					yp.push(y);
					test[x][y] = count;
				}
				while (!xp.empty() && !yp.empty())
				{
					int i = xp.back();
					int j = yp.back();
					////////////////
					if (i + 1 < 6)
					{
						if (level[i + 1][j] == '#')
						{
							if (test[i + 1][j] == 0)
							{
								xp.push(i + 1);
								yp.push(j);
								test[i + 1][j] = count;
							}
						}
					}
					////////////
					if (j + 1 < 6)
					{
						if (level[i][j + 1] == '#')
						{
							if (test[i][j + 1] == 0)
							{
								xp.push(i);
								yp.push(j + 1);
								test[i][j+1] = count;
							}
						}
					}
					////////////
					if (j - 1 >= 0)
					{
						if (level[i][j - 1] == '#')
						{
							if (test[i][j - 1] == 0)
							{
								xp.push(i);
								yp.push(j - 1);
								test[i][j - 1] = count;
							}
						}
					}

					////////////////
					if (i - 1 < 0)
					{
						if (level[i - 1][j] == '#')
						{
							if (test[i - 1][j] == 0)
							{
								xp.push(i - 1);
								yp.push(j);
								test[i - 1][j] = count;
							}
						}
					}

					count++;
				}
			}
		}


	}

	for (int i = 0; i < 6; i++)
	{
		for (int j = 0; j < 6; j++)
		{
			if (i > 1)
			{
				valid = false;
			}
		}
	}

	return valid;
}
