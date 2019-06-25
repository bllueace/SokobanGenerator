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
		pressed = true;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::R) && pressed == false)
	{
		//cout << "Generating new layout..." << endl;
		initialiseLevel();
		//pressed = true;
	}
	if (event.key.code == sf::Keyboard::G)
	{
		cout << "Generating new layout..." << endl;
		initialiseLevel();
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
	int set[400];
	int count = 0;
	for (int i = 0; i < 20; i++)
	{
		for (int j = 0; j < 20; j++)
		{
			set[count] = level.getContent(i, j);
			count++;
		}
	}
	//load tilemap from an array
	if (!map.load("gfx/UpdatedTileSet.png", sf::Vector2u(64, 64), set, 20,20))
		return;

	for (int i = 0; i < 20; i++)
	{
		for (int j = 0; j < 20; j++)
		{
			levelData[i][j] = level.getContent(i, j);
		}
	}

	solver.getCurrentState(levelData);
}

void Game::update(float deltaTime)
{

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
}

Game::~Game()
{
}
