#include "LevelGenerator.h"
#include <vcruntime_string.h>
#include <xutility>
#include <queue>
#include <iomanip>
#include <string>
#include <memory>
#include <iostream>
#include <stdio.h>

LevelGenerator::LevelGenerator(StateManager& a_game, sf::Font& a_font) :
	GameState(a_game),
	font(a_font)
{
	templates = new templateShapes;
	srand(time(NULL));

	menuBackground1.loadFromFile("gfx/MainMenu.png");
	bgr1.setTexture(&menuBackground1);
	bgr1.setSize(sf::Vector2f(720, 704));

	for (int i = 0; i < MAX_NUMBER_OF_ITEMS-1; i++)
	{
		menu[i].setCharacterSize(25);
	}

	menu[0].setFont(font);
	menu[0].setFillColor(sf::Color::Blue);
	menu[0].setCharacterSize(40);
	menu[0].setString("Num Levels: " + to_string(numLevels));
	menu[0].setPosition(sf::Vector2f(WIDTH / 2 - 50, HEIGHT / (MAX_NUMBER_OF_ITEMS + 1) * 1));

	menu[1].setFont(font);
	menu[1].setFillColor(sf::Color::Red);
	menu[1].setString("Size X:" + to_string(tempX));
	menu[1].setPosition(sf::Vector2f(WIDTH / 2 - 50, HEIGHT / (MAX_NUMBER_OF_ITEMS + 1) * 1.4));

	menu[2].setFont(font);
	menu[2].setFillColor(sf::Color::Red);
	menu[2].setString("Size Y:" + to_string(tempY));
	menu[2].setPosition(sf::Vector2f(WIDTH / 2 - 50, HEIGHT / (MAX_NUMBER_OF_ITEMS + 1) * 1.8));

	menu[3].setFont(font);
	menu[3].setFillColor(sf::Color::Red);
	menu[3].setString("Num Boxes: " + to_string(numBoxGoal));
	menu[3].setPosition(sf::Vector2f(WIDTH / 2 - 50, HEIGHT / (MAX_NUMBER_OF_ITEMS + 1) * 2.2));

	menu[4].setFont(font);
	menu[4].setFillColor(sf::Color::Red);
	menu[4].setString("Generate");
	menu[4].setPosition(sf::Vector2f(WIDTH / 2 - 50, HEIGHT / (MAX_NUMBER_OF_ITEMS + 1) * 2.6));

	menu[5].setFont(font);
	menu[5].setFillColor(sf::Color::Red);
	menu[5].setString("Back");
	menu[5].setPosition(sf::Vector2f(WIDTH / 2 - 50, HEIGHT / (MAX_NUMBER_OF_ITEMS + 1) * 3));

	menu[6].setFont(font);
	menu[6].setFillColor(sf::Color::Red);
	menu[6].setCharacterSize(20);
	menu[6].setString("WARNING!!! Can take several minutes to generate this size.");
	menu[6].setPosition(sf::Vector2f( 20, HEIGHT / (MAX_NUMBER_OF_ITEMS + 1) * 5.3));

	//makeLevel();
}

LevelGenerator::~LevelGenerator()
{
	delete templates;
}

//#pragma optimize("", off)
void LevelGenerator::makeLevel()
{

	for (int i = 0; i < numLevels; i++) 
	{
		the_clock::time_point start = the_clock::now();
		do //while the level is not solvable
		{
			do // while there are no boxes that cant reach a goal on the sides
			{
				do //while there are more than one closed off rooms
				{
					generateLevel(tempX, tempY);
					//prepareLevelForSolver();

				} while (!contFloor(emptyLevel));//&& !noTrappedFloors()

				addPlayer();
				addBoxes(numBoxGoal);
				addGoals(numBoxGoal);
				print(emptyLevel);
				noGoalNextToWallBox++;
			} while (!checkStuckBoxes());

			prepareLevelForSolver();
			solver.getCurrentState(numericalLevel);
			solution  = solver.solve();
			cout << endl << solution;
			//keep track of number of levels tried
			attempts++;
		} while (!solver.goodLevel);
		the_clock::time_point end = the_clock::now();
		time_taken = duration_cast<milliseconds>(end - start).count();
		time_taken = time_taken / 1000;
		saveGenLevels();
		writeTestData("Test.csv", time_taken,i+1, true);

		//reset data gathering variables
		shapesTried = 0;
		attempts = 0;
		noGoalNextToWallBox = 0;
		trapedBox = 0;
	}
}

//#pragma optimize("", on)
int LevelGenerator::random(int min, int max)
{
	static bool first = true;
	if (first)
	{
		srand(time(NULL)); //seeding for the first time only!
		first = false;
	}
	return min + rand() % ((max + 1) - min);
}

void LevelGenerator::print(array<array<char, 11>, 11> level)
{
	//const int rows = std::extent<decltype(emptyLevel), 0>::value;
	//const int cols = std::extent<decltype(emptyLevel), 1>::value;
	system("CLS");
	for (int i = 0; i < 11; i++) {
		for (int j = 0; j < 11; j++) {
			cout << setw(2);
			cout << level[i][j] << " ";
		}
		cout << endl;
	}
}
//rotates an 2d array 
void LevelGenerator::rotate90(array<array<char, 5>, 5> arr)
{
	array<array<char, 5>, 5> result;
	for (int i = 0; i < 5; i++)
		for (int j = 0; j < 5; j++)
			result[i][j] = arr[5 - j - 1][i];
	temp.swap(result);
	//memcpy(temp, result, sizeof temp);
}
//flip the array up
void LevelGenerator::flipShapeU(array<array<char, 5>, 5> arr)
{
	array<array<char, 5>, 5> result;
	for (int i = 0; i < 5; i++)
		for (int y = 0; y < 5; y++)
			result[i][y] = arr[5 - i - 1][y];

	temp.swap(result);
	//memcpy(temp, result, sizeof temp);
}
//flip the array right
void LevelGenerator::flipShapeR(array<array<char, 5>, 5> arr)
{
	array<array<char, 5>, 5> result;
	for (int i = 0; i < 5; i++)
		for (int y = 0; y < 5; y++)
			result[i][y] = arr[i][5 - y - 1];

	temp.swap(result);
	//memcpy(temp, result, sizeof temp);
}

void LevelGenerator::generateLevel(int height, int width)
{
	//initialize the array
	blockPosX = 1;
	blockPosY = 1;
	for (int i = 0; i < 11; i++)
	{
		for (int j = 0; j < 11; j++)
		{
			emptyLevel[i][j] = '*';
		}
	}
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
					if (blockPosX + k < 11 && blockPosY + p < 11)
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
				blockPosX = 1
					;
			}
		}
		if (blockPosY > width - 1)
			return;

		//count++;
		////return if cant find a suitable shape
		//if (count > 10000)
		//	generateLevel(tempX, tempY);
	}
}

void LevelGenerator::getRandomShape()
{
	shapesTried++;
	shape = rand() % 17 + 1;
	//shape = 7;
	switch (shape)
	{
	case 1:
		//memcpy(temp, templates.shape1, sizeof templates.shape1);
		temp.swap(templates->shape1);
		break;
	case 2:
		//memcpy(temp, templates.shape2, sizeof templates.shape2);
		temp.swap(templates->shape2);

		break;
	case 3:
		// memcpy(temp, templates.shape2, sizeof templates.shape2);
		temp.swap(templates->shape3);

		break;
	case 4:
		//memcpy(temp, templates.shape4, sizeof templates.shape4);
		temp.swap(templates->shape4);
		break;
	case 5:
		//memcpy(temp, templates.shape5, sizeof templates.shape5);
		temp.swap(templates->shape5);
		break;
	case 6:
		//memcpy(temp, templates.shape6, sizeof templates.shape6);
		temp.swap(templates->shape6);
		break;
	case 7:
		//memcpy(temp, templates.shape7, sizeof templates.shape7);
		temp.swap(templates->shape7);
		break;
	case 8:
		//memcpy(temp, templates.shape8, sizeof templates.shape8);
		temp.swap(templates->shape8);
		break;
	case 9:
		//memcpy(temp, templates.shape9, sizeof templates.shape9);
		temp.swap(templates->shape9);
		break;
	case 10:
		//memcpy(temp, templates.shape10, sizeof templates.shape10);
		temp.swap(templates->shape10);
		break;
	case 11:
		//memcpy(temp, templates.shape11, sizeof templates.shape11);
		temp.swap(templates->shape11);
		break;
	case 12:
		//memcpy(temp, templates.shape12, sizeof templates.shape12);
		temp.swap(templates->shape12);
		break;
	case 13:
		//memcpy(temp, templates.shape13, sizeof templates.shape13);
		temp.swap(templates->shape13);
		break;
	case 14:
		//memcpy(temp, templates.shape11, sizeof templates.shape11);
		temp.swap(templates->shape11);
		break;
	case 15:
		//memcpy(temp, templates.shape15, sizeof templates.shape15);
		temp.swap(templates->shape15);
		break;
	case 16:
		//memcpy(temp, templates.shape16, sizeof templates.shape16);
		temp.swap(templates->shape16);
		break;
	case 17:
		//memcpy(temp, templates.shape17, sizeof templates.shape17);
		temp.swap(templates->shape17);
		break;
	}


	//rotate x times
	int rnd = random(0, 4);
	for (int r = 0; r < rnd; r++)
	{
		rotate90(temp);
	}
	//flip x direction
	rnd = random(0, 3);
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
//	contFloor(emptyLevel);
	return emptyLevel[i][j];

}

bool LevelGenerator::canFit(array<array<char, 11>, 11> level, array<array<char, 5>, 5> arr, int startX, int startY, int hight, int width, int size)
{
	bool fit = true;
	//check top
	for (int i = 0; i < size; i++)
	{
		if (startY + i < width)
		{
			if (level[startX][startY + i] != ' ')
			{
				if (level[startX][startY + i] != arr[0][i])
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
				if (level[startX + i][startY] != arr[i][0])
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
					if (level[startX + 4][startY+i] != arr[4][i])
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
					if (level[startX + i][startY + 4] != arr[i][4])
					{
						fit = false;
					}
				}
			}
		}
	}
	return fit;
}

bool LevelGenerator::contFloor(array<array<char, 11>, 11> level)
{
	int num_spaces = 0;
	counter = 0;

	for (int i = 0; i <= tempX+1; i++)
	{
		for (int j = 0; j <= tempY+1; j++)
		{
			switch (level[i][j])
			{
			case '#': //walls
				lev[i][j] = -2;
				break;
			case ' ': //Empty
				lev[i][j] = -1;
				num_spaces++;
				break;
			case '*':
				lev[i][j] = -9;
			}
		}
	}

	if (num_spaces <= 10) return false;

	for (int i = 0; i <= tempX + 1; i++)
	{
		for (int j = 0; j <= tempY + 1; j++)
		{
			if (lev[i][j] == -1)
			{
				lev[i][j] = 0;
				goto LOOP;
			}
		}
	}


	LOOP:for (int i = 0; i < (tempX + tempY); i++)
	{
		for (int i = 0; i <= tempX; i++) {
			for (int j = 0; j <= tempY; j++)
			{
				if (lev[i][j] == counter)
				{
					fillout(i + 1, j, counter + 1);
					fillout(i - 1, j, counter + 1);
					fillout(i, j + 1, counter + 1);
					fillout(i, j - 1, counter + 1);

				}
			}
		}
		counter++;
	}

		 //see if there are any unvisited cells left/ if so then return false
		 for (int i = 0; i <= tempX + 1; i++)
		 {
			 for (int j = 0; j <= tempY + 1; j++)
			 {
				 if (lev[i][j] == -1)
				 {
					 return false;
				 }
			 }
		 }

//	system("CLS");
//	print(lev);
	return true;
}

void LevelGenerator::fillout(int x, int y, int value)
{
	if ((x >= 0) && (y >= 0) && (x < tempX+1) && (y < tempY+1) && (lev[x][y] == -1))
	{
		lev[x][y] = value;
	}
}

void LevelGenerator::addPlayer()
{
	//const int rows = std::extent<decltype(emptyLevel), 0>::value;
	//const int cols = std::extent<decltype(emptyLevel), 1>::value;
	bool placed = false;

	while (!placed)
	{
		int x = random(1, placementCheck);
		int y = random(1, placementCheck);
		if (emptyLevel[x][y] == ' ')
		{
			placed = true;
			emptyLevel[x][y] = '@';
		}
	}
}

void LevelGenerator::addGoals(int numGoals)
{
	//const int rows = std::extent<decltype(emptyLevel), 0>::value;
	//const int cols = std::extent<decltype(emptyLevel), 1>::value;
	bool placed = false;
	int count = 0;
	while (!placed)
	{
		int x = random(1, placementCheck - 1);
		int y = random(1, placementCheck - 1);

		if (emptyLevel[x][y] == ' ')
		{
			emptyLevel[x][y] = '.';
			numGoals--;

			if (numGoals <= 0)
			{
				placed = true;
			}
		}
	}
}

bool LevelGenerator::checkCorneredBoxes(int x, int y)
{
	//check top right corner
	if ((emptyLevel[x + 1][y] == '#' || emptyLevel[x + 1][y] == '*') &&
		(emptyLevel[x][y - 1] == '#' || emptyLevel[x][y - 1] == '*'))
		return false;
	//check bottom right corner
	else if ((emptyLevel[x + 1][y] == '#' || emptyLevel[x + 1][y] == '*')
		&& (emptyLevel[x][y + 1] == '#' || emptyLevel[x][y + 1] == '*'))
		return false;
	//check bottom left corner
	else if ((emptyLevel[x - 1][y] == '#' || emptyLevel[x - 1][y] == '*')
		&& (emptyLevel[x][y + 1] == '#' || emptyLevel[x][y + 1] == '*'))
		return false;
	//check top left corner
	else if ((emptyLevel[x - 1][y] == '#' || emptyLevel[x - 1][y] == '*')
		&& (emptyLevel[x][y - 1] == '#' || emptyLevel[x][y - 1] == '*'))
		return false;

	return true;
}

bool LevelGenerator::checkStuckBoxes()
{
	//the values might seem wrong but because the array gets oriented at one point it gets a bit funky

	int wallBoxCount = 0;
	int wallGoalCount = 0;
	bool left = false, right = false, top = false, bottom = false;
	//check left row
	for (int i = 0; i <= tempX+1; i++)
	{
		if (emptyLevel[i][1] == '$')
			wallBoxCount++;
		if (emptyLevel[i][1] == '.')
			wallGoalCount++;
	}
	if (wallGoalCount >= wallBoxCount)
		left = true;

	wallBoxCount = 0;
	wallGoalCount = 0;
	//check bottom?
	for (int i = 0; i <= tempY+1; i++)
	{
		if (emptyLevel[tempX][i] == '$')
			wallBoxCount++;
		if (emptyLevel[tempX][i] == '.')
			wallGoalCount++;

	}
	if (wallGoalCount >= wallBoxCount)
		bottom = true;

	wallBoxCount = 0;
	wallGoalCount = 0;
	//check top row
	for (int i = 0; i <= tempY+1; i++)
	{
		if (emptyLevel[1][i] == '$')
			wallBoxCount++;
		if (emptyLevel[1][i] == '.')
			wallGoalCount++;

	}
	if (wallGoalCount >= wallBoxCount)
		top = true;

	wallBoxCount = 0;
	wallGoalCount = 0;
	//check right row
	for (int i = 0; i <= tempX+1; i++)
	{

		if (emptyLevel[i][tempY] == '$')
			wallBoxCount++;
		if (emptyLevel[i][tempY] == '.')
			wallGoalCount++;
	}
	if (wallGoalCount >= wallBoxCount)
		right = true;

	wallBoxCount = 0;
	wallGoalCount = 0;

	if (top && bottom && left && right)
		return true;
	else
		return false;
}

bool LevelGenerator::noTrappedFloors()
{
	for (int i = 0; i <= tempX + 1; i++)
	{
		for (int j = 0; j <= tempY + 1; j++)
		{
			if (numericalLevel[i][j] == 0)
			{
				wallCount = 0;
				if (numericalLevel[i + 1][j] == 1)
					wallCount++;
				else
					wallCount++;
				if (numericalLevel[i - 1][j] == 1)
					wallCount++;
				else
					wallCount++;
				if (numericalLevel[i][j + 1] == 1)
					wallCount++;
				else
					wallCount++;
				if (numericalLevel[i][j - 1] == 1)
					wallCount++;
				else
					wallCount++;

				if (wallCount > 2)
					return false;
			}
		}
	}
	return true;
}

void LevelGenerator::addBoxes(int numBox)
{
	//const int rows = std::extent<decltype(emptyLevel), 0>::value;
	//const int cols = std::extent<decltype(emptyLevel), 1>::value;
	bool placed = false;
	//int count = 0;
	while (!placed)
	{
		int x = random(1, tempX ); // was  - 2
		int y = random(1, tempY ); // was - 2

		if (emptyLevel[x][y] == ' ')
		{
			//TODO: FIX THE CRASH THAT OCCURES 
			if (checkCorneredBoxes(x,y))
			{
				emptyLevel[x][y] = '$';
				numBox--;
			}

			if (numBox <= 0)
			{
				placed = true;
			}
		}
		trapedBox++;
	}
}

void LevelGenerator::saveGenLevels()
{
	string filename;

	//filename = "Level " + to_string(num);
	filename = to_string(num);
	filename += ".txt";
	ofstream levels("levels\\" + filename, ofstream::out);

	//ofs.open("test.txt");

	//levels << "Level " + to_string(num) << endl;
	levels << to_string(num) << endl;

	for (int count = 0; count < 11; count++)
	{
		for (int index = 0; index < 11; index++)
		{
			levels << emptyLevel[count][index]; // <<  " " 
		}
		levels << endl;
	}

	levels << endl << endl << "Solution: ";
	levels << endl  << solution;
	levels << endl << endl << "Complete solution took: " << time_taken << "ms.";


	levels.close();

	num++;
}

void LevelGenerator::update(sf::Time elapsed, int playerInp)
{

}

void LevelGenerator::draw(VirtualScreen & screen)
{
	screen.draw(bgr1);
	for (int i = 0; i < MAX_NUMBER-1; i++)
	{
		screen.draw(menu[i]);
	}
	if ((tempX >= 9 && tempY >= 6 && numBoxGoal >= 4) ||
		(tempY >= 9 && tempX >=6 && numBoxGoal >= 4) ||
		(tempX == 9 && tempY == 9 && numBoxGoal >= 4) || (numBoxGoal == 5))
	{
		screen.draw(menu[6]);
	}
}

void LevelGenerator::event(sf::Time elapsed, sf::Event a_event)
{
	if (a_event.type == sf::Event::KeyPressed)
	{
		if (a_event.key.code == sf::Keyboard::BackSpace)
			game.changeState(std::unique_ptr<GameState>(new Menu(game, font)));
		if (a_event.key.code == sf::Keyboard::Down)
			MoveDown();
		if (a_event.key.code == sf::Keyboard::Up)
			MoveUp();
		if (a_event.key.code == sf::Keyboard::Escape)
		{
			//quit the game and delete all current levels
			std::string command = "del /Q ";
			std::string path = "levels\\*.txt";
			system(command.append(path).c_str());
			//std::cout << rv << std::endl;
			//system("pause");
			exit(EXIT_FAILURE);
		}
		if (a_event.key.code == sf::Keyboard::Enter)
		{
			switch (getPressedItem())
			{
			default:
				break;
			case 4:
				makeLevel();
				break;
			case 5:
				game.changeState(std::unique_ptr<GameState>(new Menu(game, font)));
				break;
			}
		}
		switch (getPressedItem())
		{
		default:
			break;
		case 0:
			if (a_event.key.code == sf::Keyboard::Right)
				if (numLevels < 5)
				{
					numLevels++;
					menu[0].setString("Num Levels: " + to_string(numLevels));
				}
			if (a_event.key.code == sf::Keyboard::Left)
				if (numLevels > 1)
				{
					numLevels--;
					menu[0].setString("Num Levels: " + to_string(numLevels));
				}
			break;
		case 1:
			if (a_event.key.code == sf::Keyboard::Right)
				if (tempX < 9)
				{
					tempX += 3;
					menu[1].setString("Size X:" + to_string(tempX));
				}
			if (a_event.key.code == sf::Keyboard::Left)
				if (tempX > 3)
				{
					if (tempX + tempY > 9)
					{
						tempX -= 3;
						menu[1].setString("Size X:" + to_string(tempX));
					}
					if (tempX + tempY < 12)
					{
						if (numBoxGoal > 3)
							numBoxGoal = 3;
						menu[3].setString("Num Boxes: " + to_string(numBoxGoal));
					}
				}
			break;
		case 2:
			if (a_event.key.code == sf::Keyboard::Right)
				if (tempY < 9)
				{
					tempY += 3;
					menu[2].setString("Size Y:" + to_string(tempY));
				}
			if (a_event.key.code == sf::Keyboard::Left)
				if (tempY > 3)
				{
					if (tempX + tempY > 9)
					{
						tempY -= 3;
						menu[2].setString("Size Y:" + to_string(tempY));
					}
					if (tempX + tempY < 12)
					{
						if (numBoxGoal > 3)
							numBoxGoal = 3;
						menu[3].setString("Num Boxes: " + to_string(numBoxGoal));
					}
				}
			break;
		case 3: 
			if (a_event.key.code == sf::Keyboard::Right)
			{
				if (tempY + tempX >= 12)
				{
					if (numBoxGoal < 5)
					{
						numBoxGoal++;
						menu[3].setString("Num Boxes: " + to_string(numBoxGoal));
					}
				}
				if (tempX + tempY <= 9)
				{
					if (numBoxGoal < 3)
					{
						numBoxGoal++;
						menu[3].setString("Num Boxes: " + to_string(numBoxGoal));
					}
				}

			}
			if (a_event.key.code == sf::Keyboard::Left)
			{
				if (numBoxGoal > 1)
				{
					numBoxGoal--;
					menu[3].setString("Num Boxes: " + to_string(numBoxGoal));
				}

			}
			break;
		}


	}
}

void LevelGenerator::pause()
{

}

void LevelGenerator::resume()
{

}

void LevelGenerator::prepareLevelForSolver()
{
	for (int i = 0; i < 11; i++)
	{
		for (int j = 0; j < 11; j++)
		{
			switch (emptyLevel[i][j])
			{
			case ' ': //Empty
				numericalLevel[i][j] = 0;
				break;
			case '#': //walls
				numericalLevel[i][j] = 1;
				break;
			case '$': //Box
				numericalLevel[i][j] = 2;
				break;
			case '.': //Goal
				numericalLevel[i][j] = 3;
				break;
			case '@': //Player
				numericalLevel[i][j] = 4;
				break;
			case '?': //Box on goal
				numericalLevel[i][j] = 5;
				break;
			case '+': //Player on goal
				numericalLevel[i][j] = 6;
				break;
			case '*': // outside environment
				numericalLevel[i][j] = 1;
				break;
			}
		}
	}
}

void LevelGenerator::MoveUp()
{
	if (selectedItem - 1 >= 0)
	{
		menu[selectedItem].setFillColor(sf::Color::Red);
		menu[selectedItem].setCharacterSize(25);
		selectedItem--;
		menu[selectedItem].setFillColor(sf::Color::Blue);
		menu[selectedItem].setCharacterSize(40);
	}
}

void LevelGenerator::MoveDown()
{
	if (selectedItem + 1 < MAX_NUMBER-1)
	{
		menu[selectedItem].setFillColor(sf::Color::Red);		
		menu[selectedItem].setCharacterSize(25);
		selectedItem++;
		menu[selectedItem].setFillColor(sf::Color::Blue);
		menu[selectedItem].setCharacterSize(40);

	}
}

void LevelGenerator::writeTestData(const std::string& name, const float& content,int levelNum, bool append /*= false*/)
{
	std::ofstream outfile;

	if (append)
	{
		outfile.open(name, std::ios_base::app);

	}
	else
		outfile.open(name);

	if (!excelFileCreated)
	{
		outfile<<"\n" << "Levels" << "," << "Time Taken/ms" << "," << "Levels Tested" << 
			"," << "Trapped" << "," << "Unreachable" << "," << "Shapes Tried " << "\n";
		//outfile.close();
		excelFileCreated = true;
	}

	outfile << "Level: " << levelNum;
	outfile << "," << content;
	outfile << "," << attempts;
	outfile << "," << trapedBox;
	outfile << "," << noGoalNextToWallBox;
	outfile << "," << shapesTried << endl;

}
