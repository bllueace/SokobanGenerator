#include "Game.h"

Game::Game(sf::RenderWindow* hwnd, Input* in)
{
	window = hwnd;
	input = in;
	state = GameState::LEVEL;
	//Load font if needed
	//if (!font.loadFromFile("font/arial.ttf"))
	//{
	//	MessageBox(NULL, L"Failed to load font", L"Error", MB_OK);
	//}

	initialiseLevel();
}

GameState Game::getState()
{
	return state;
}

void Game::handleInput()
{
	//if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space) && pressed == false)
	//{
	//	cout << "Solving..." << endl;
	//	std::cout << solver.solve() << std::endl;
	//	//pressed = true;
	//}
}

void Game::initialiseLevel()
{
	//cout << "Please enter which level to play (1-5): " << endl;
	//cin >> playerInp;
	numGoals = 0;
	level.initialize(playerInp);
	//level.print();

	//change the 2d array to normal array in order to access tilemap
	int count = 0;
	for (int i = 0; i < 11; i++)
	{
		for (int j = 0; j < 11; j++)
		{
			if (level.getContent(i, j) == 4)
			{
				playerPos.x = i;
				playerPos.y = j;
			}

			if (level.getContent(i, j) == 3)
				numGoals++;

			set[i][j] = level.getContent(i, j);
			count++;
		}
	}
	//load tilemap from an array
	if (!map.load("gfx/UpdatedTileSet.png", sf::Vector2u(64, 64), set, 11,11))
		return;
}

void Game::resetTile(int x, int y)
{
	if (set[x][y] == 4)
		set[x][y] = 0;
	else if (set[x][y] == 6)
		set[x][y] = 3;
	else if (set[x][y] == 2)
		set[x][y] = 0;
	else if (set[x][y] == 5)
	{
		set[x][y] = 3;
		//numGoals++;
	}
}

void Game::update(int playerMove)
{
	//handleInput();
	switch (playerMove)
	{
		//move down
	case 1:
		if ((set[playerPos.x + 1][playerPos.y] == 0) || (set[playerPos.x +1][playerPos.y] == 3))
		{
			resetTile(playerPos.x, playerPos.y);

			if (set[playerPos.x + 1][playerPos.y] == 0)
				set[playerPos.x + 1][playerPos.y] = 4;
			if (set[playerPos.x + 1][playerPos.y] == 3)
				set[playerPos.x + 1][playerPos.y] = 6;

			playerPos.x++;
			if (!map.load("gfx/UpdatedTileSet.png", sf::Vector2u(64, 64), set, 11, 11))
				return;
		}
		else if (set[playerPos.x + 1][playerPos.y] == 2 && set[playerPos.x + 2][playerPos.y] != 1)
		{
			if (set[playerPos.x + 2][playerPos.y] == 0)
			{
				set[playerPos.x + 2][playerPos.y] = 2;
				if (set[playerPos.x + 1][playerPos.y] == 2)
					set[playerPos.x + 1][playerPos.y] = 0;
				else if (set[playerPos.x + 1][playerPos.y] == 5)
				{
					set[playerPos.x + 1][playerPos.y] = 3;
					numGoals++;
				}
			}
			else if (set[playerPos.x + 2][playerPos.y] == 3)
			{
				set[playerPos.x + 2][playerPos.y] = 5;
				numGoals--;
				if (set[playerPos.x + 1][playerPos.y] == 2)
					set[playerPos.x + 1][playerPos.y] = 0;
				else if (set[playerPos.x + 1][playerPos.y] == 5)
				{
					set[playerPos.x + 1][playerPos.y] = 3;
					numGoals++;
				}
			}

			resetTile(playerPos.x, playerPos.y);

			if (set[playerPos.x + 1][playerPos.y] == 0)
				set[playerPos.x + 1][playerPos.y] = 4;
			if (set[playerPos.x + 1][playerPos.y] == 3)
				set[playerPos.x + 1][playerPos.y] = 6;

			playerPos.x++;
			if (!map.load("gfx/UpdatedTileSet.png", sf::Vector2u(64, 64), set, 11, 11))
				return;
		}
		break;
	case 2:
		if (set[playerPos.x - 1][playerPos.y] == 0 || set[playerPos.x - 1][playerPos.y] == 3)
		{
			resetTile(playerPos.x, playerPos.y);

			if (set[playerPos.x - 1][playerPos.y] == 0)
				set[playerPos.x - 1][playerPos.y] = 4;
			else if (set[playerPos.x - 1][playerPos.y] == 3)
				set[playerPos.x - 1][playerPos.y] = 6;

			playerPos.x--;
			if (!map.load("gfx/UpdatedTileSet.png", sf::Vector2u(64, 64), set, 11, 11))
				return;
		}
		else if (set[playerPos.x - 1][playerPos.y] == 2 && set[playerPos.x - 2][playerPos.y] != 1)
		{
			if (set[playerPos.x - 2][playerPos.y] == 0)
			{
				set[playerPos.x - 2][playerPos.y] = 2;
				if (set[playerPos.x - 1][playerPos.y] == 2)
					set[playerPos.x - 1][playerPos.y] = 0;
				else if (set[playerPos.x - 1][playerPos.y] == 5)
				{
					set[playerPos.x - 1][playerPos.y] = 3;
					numGoals--;
				}
			}
			else if (set[playerPos.x - 2][playerPos.y] == 3)
			{
				set[playerPos.x - 2][playerPos.y] = 5;
				numGoals--;
				if (set[playerPos.x - 1][playerPos.y] == 2)
					set[playerPos.x - 1][playerPos.y] = 0;
				else if (set[playerPos.x - 1][playerPos.y] == 5)
				{
					set[playerPos.x - 1][playerPos.y] = 3;
					numGoals--;
				}
			}

			resetTile(playerPos.x, playerPos.y);

			if (set[playerPos.x - 1][playerPos.y] == 0)
				set[playerPos.x - 1][playerPos.y] = 4;
			if (set[playerPos.x - 1][playerPos.y] == 3)
				set[playerPos.x - 1][playerPos.y] = 6;
			playerPos.x--;
			if (!map.load("gfx/UpdatedTileSet.png", sf::Vector2u(64, 64), set, 11, 11))
				return;
		}
		break;
	case 3:
		if (set[playerPos.x][playerPos.y - 1] == 0 || set[playerPos.x][playerPos.y - 1] == 3)
		{
			resetTile(playerPos.x, playerPos.y);

			if (set[playerPos.x][playerPos.y - 1] == 0)
				set[playerPos.x][playerPos.y - 1] = 4;
			else if (set[playerPos.x][playerPos.y - 1] == 3)
				set[playerPos.x][playerPos.y - 1] = 6;

			playerPos.y--;
			if (!map.load("gfx/UpdatedTileSet.png", sf::Vector2u(64, 64), set, 11, 11))
				return;
		}
		else if (set[playerPos.x][playerPos.y - 1] == 2 && set[playerPos.x][playerPos.y - 2] != 1)
		{

			if (set[playerPos.x][playerPos.y-2] == 0)
			{
				set[playerPos.x][playerPos.y-2] = 2;
				if (set[playerPos.x][playerPos.y-1] == 2)
					set[playerPos.x][playerPos.y-1] = 0;
				else if (set[playerPos.x][playerPos.y-1] == 5)
				{
					set[playerPos.x ][playerPos.y-1] = 3;
					numGoals++;
				}
			}
			else if (set[playerPos.x ][playerPos.y-2] == 3)
			{
				set[playerPos.x ][playerPos.y-2] = 5;
				numGoals--;
				if (set[playerPos.x ][playerPos.y-1] == 2)
					set[playerPos.x ][playerPos.y-1] = 0;
				else if (set[playerPos.x ][playerPos.y-1] == 5)
				{
					set[playerPos.x ][playerPos.y-1] = 3;
					numGoals++;
				}
			}

			resetTile(playerPos.x, playerPos.y);

			if (set[playerPos.x][playerPos.y-1] == 0)
				set[playerPos.x][playerPos.y-1] = 4;
			if (set[playerPos.x][playerPos.y-1] == 3)
				set[playerPos.x][playerPos.y-1] = 6;
			playerPos.y--;
			if (!map.load("gfx/UpdatedTileSet.png", sf::Vector2u(64, 64), set, 11, 11))
				return;
		}
		break;
	case 4:
		if (set[playerPos.x][playerPos.y + 1] == 0 || set[playerPos.x][playerPos.y + 1] == 3)
		{
			resetTile(playerPos.x, playerPos.y);
	
			if (set[playerPos.x][playerPos.y + 1] == 0)
				set[playerPos.x][playerPos.y + 1] = 4;
			else if (set[playerPos.x][playerPos.y + 1] == 3)
				set[playerPos.x][playerPos.y + 1] = 6;

			playerPos.y++;
			if (!map.load("gfx/UpdatedTileSet.png", sf::Vector2u(64, 64), set, 11, 11))
				return;
		}
		else if (set[playerPos.x][playerPos.y + 1] == 2 && set[playerPos.x][playerPos.y + 2] != 1)
		{

			if (set[playerPos.x][playerPos.y + 2] == 0)
			{
				set[playerPos.x][playerPos.y + 2] = 2;
				if (set[playerPos.x][playerPos.y + 1] == 2)
					set[playerPos.x][playerPos.y + 1] = 0;
				else if (set[playerPos.x][playerPos.y + 1] == 5)
				{
					set[playerPos.x][playerPos.y + 1] = 3;
					numGoals++;
				}
			}
			else if (set[playerPos.x][playerPos.y + 2] == 3)
			{
				set[playerPos.x][playerPos.y + 2] = 5;
				numGoals--;
				if (set[playerPos.x][playerPos.y + 1] == 2)
					set[playerPos.x][playerPos.y + 1] = 0;
				else if (set[playerPos.x][playerPos.y + 1] == 5)
				{
					set[playerPos.x][playerPos.y + 1] = 3;
					numGoals++;
				}
			}

			resetTile(playerPos.x, playerPos.y);

			if (set[playerPos.x][playerPos.y + 1] == 0)
				set[playerPos.x][playerPos.y + 1] = 4;
			if (set[playerPos.x][playerPos.y + 1] == 3)
				set[playerPos.x][playerPos.y + 1] = 6;
			playerPos.y++;
			if (!map.load("gfx/UpdatedTileSet.png", sf::Vector2u(64, 64), set, 11, 11))
				return;
		}
		break;
	}
	if (numGoals <= 0)
	{
		cout << "All goals reached" << endl;
	}
}

void Game::render()
{
	//begin draw
	beginDraw();
	//draw everything
	window->draw(map);
	//end draw
	endDraw();
}

void Game::beginDraw()
{
	window->clear(sf::Color::Black);
}
void Game::endDraw()
{
	window->display();
}

void Game::getSolutionString(string sol)
{
	for (int i = 0; i < sol.length(); i++)
	{
		solution.push(sol[i]);
	}
}

void Game::runSolution()
{

	for (int i = 0; i < 11; i++)
	{
		for (int j = 0; j < 11; j++)
		{
			//levelData[i][j] = level.getContent(i, j);
			levelData[i][j] = set[i][j];
		}
	}

	solver.getCurrentState(levelData);

	std::cout << "Finding a solution..." << std::endl;
	std::cout << solver.solve() << std::endl;
}

Game::~Game()
{
}
