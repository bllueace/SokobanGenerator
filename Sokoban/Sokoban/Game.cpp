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

	cout << "Please enter which level to play (1-5): ";
	cin >> playerInp; 

	level.initialize(playerInp);
	level.print();

	//change the 2d array to normal array in order to acces tilemap
	int set[289];
	int count = 0;
	for (int i = 0; i < 17; i++)
	{
		for (int j = 0; j < 17; j++)
		{
			set[count] = level.getContent(i, j);
			count++;
		}
	}
	//load tilemap from an array
	if (!map.load("tileset.png", sf::Vector2u(32, 32), set, 17, 17))
		return;

	for (int i = 0; i < 17; i++)
	{
		for (int j = 0; j < 17; j++)
		{
			levelData[i][j] = level.getContent(i, j);
		}
	}

	solver.getCurrentState(levelData);
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
