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
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space) && pressed == false)
	{
		cout << "Solving..." << endl;
		std::cout << solver.solve() << std::endl;
		//pressed = true;
	}
}

void Game::initialiseLevel()
{
	//cout << "Please enter which level to play (1-5): " << endl;
	//cin >> playerInp;

	level.initialize(playerInp);
	//level.print();

	//change the 2d array to normal array in order to access tilemap
	int set[121];
	int count = 0;
	for (int i = 0; i < 11; i++)
	{
		for (int j = 0; j < 11; j++)
		{
			set[count] = level.getContent(i, j);
			count++;
		}
	}
	//load tilemap from an array
	if (!map.load("gfx/UpdatedTileSet.png", sf::Vector2u(64, 64), set, 11,11))
		return;

	for (int i = 0; i < 11; i++)
	{
		for (int j = 0; j < 11; j++)
		{
			levelData[i][j] = level.getContent(i, j);
		}
	}

	solver.getCurrentState(levelData);
	//pressed = false;
}

void Game::update(int playerMove)
{
	////handleInput();
	//switch (playerMove)
	//{
	//	//move right
	//case 1:
	//	if (set[playerPos.x + 1][playerPos.y] == 0 || set[playerPos.x + 1][playerPos.y] == 3)
	//	{
	//		if (set[playerPos.x][playerPos.y] == 4)
	//			set[playerPos.x][playerPos.y] = 0;
	//		if (set[playerPos.x][playerPos.y] == 6)
	//			set[playerPos.x][playerPos.y] = 3;

	//		if (set[playerPos.x + 1][playerPos.y] == 0)
	//			set[playerPos.x + 1][playerPos.y] = 4;
	//		if (set[playerPos.x + 1][playerPos.y] == 3)
	//			set[playerPos.x + 1][playerPos.y] == 6;

	//		playerPos.x++;
	//		if (!map.load("gfx/UpdatedTileSet.png", sf::Vector2u(64, 64), set, 11, 11))
	//			return;
	//	}
	//	else if (set[playerPos.x + 1][playerPos.y] == 2 && set[playerPos.x + 2][playerPos.y] != 1)
	//	{
	//		if (set[playerPos.x + 2][playerPos.y] == 0)
	//			set[playerPos.x + 2][playerPos.y] = 2;
	//		if (set[playerPos.x + 2][playerPos.y] == 3)
	//		{
	//			set[playerPos.x + 2][playerPos.y] == 5;
	//			numGoals--;
	//		}
	//		/////
	//		if (set[playerPos.x][playerPos.y] = 4)
	//			set[playerPos.x][playerPos.y] = 0;
	//		if (set[playerPos.x][playerPos.y] = 6)
	//			set[playerPos.x][playerPos.y] = 3;


	//		if (set[playerPos.x + 1][playerPos.y] = 2)
	//			set[playerPos.x + 1][playerPos.y] = 4;
	//		if (set[playerPos.x + 1][playerPos.y] = 5)
	//		{
	//			set[playerPos.x + 1][playerPos.y] = 6;
	//			numGoals++;
	//		}



	//		playerPos.x++;
	//		if (!map.load("gfx/UpdatedTileSet.png", sf::Vector2u(64, 64), set, 11, 11))
	//			return;
	//	}
	//	else if (set[playerPos.x + 1][playerPos.y] == 2 && set[playerPos.x + 2][playerPos.y] == 3)
	//	{

	//	}
	//	else if ((set[playerPos.x + 1][playerPos.y] == 1) ||
	//		(set[playerPos.x + 1][playerPos.y] == 2 && set[playerPos.x + 2][playerPos.y] == 1))
	//	{
	//		break;
	//	}
	//	break;
	//case 2:
	//	break;
	//case 3:
	//	break;
	//case 4:
	//	break;
	//case 0:
	//	break;
	//}
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
	std::cout << "Finding a solution..." << std::endl;
	std::cout << solver.solve() << std::endl;
}

Game::~Game()
{
}
