#include "Game.h"
#include <memory>
#include <iostream>
#include "Menu.h"

Game::Game(StateManager& a_game, sf::Font& a_font, bool genORno) :
	GameState(a_game),
	font(a_font)
{
	//initialize ui elements
	ui[0].setFont(font);
	ui[0].setCharacterSize(30);
	ui[0].setFillColor(sf::Color::Blue);
	ui[0].setString("Level: " + to_string(numLevel));
	ui[0].setPosition(sf::Vector2f(292, 20));

	//assign the bool from main menu that determines if playing player genreated levels or pre generated ones.
	genOrNo = genORno;

	initialiseLevel();
}

void Game::initialiseLevel()
{
		numGoals = 0;
		if (!level.initialize(numLevel, genOrNo))
			return;

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
		for (int i = 0; i < 11; i++)
		{
			for (int j = 0; j < 11; j++)
			{
				levelData[i][j] = set[i][j];
			}
		}

	//load tile map from an array
	if (!map.load("gfx/UpdatedTileSet.png", sf::Vector2u(64, 64), set, 11, 11))
		return;
}

void Game::nextLevel()
{
	numGoals = 0;
	level.initialize(numLevel, genOrNo);

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
	for (int i = 0; i < 11; i++)
	{
		for (int j = 0; j < 11; j++)
		{
			levelData[i][j] = set[i][j];
		}
	}

	//load tilemap from an array
	if (!map.load("gfx/UpdatedTileSet.png", sf::Vector2u(64, 64), set, 11, 11))
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
	}
}

void Game::update(sf::Time elapsed, int playerInp)
{
	if (!level.initialize(numLevel, genOrNo))
	{
		game.changeState(std::unique_ptr<GameState>(new Menu(game, font)));
		return;
	}
	switch (playerInp)
	{
		//move down
	case 1:
		if ((set[playerPos.x + 1][playerPos.y] == 0) || (set[playerPos.x + 1][playerPos.y] == 3))
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
		else if (set[playerPos.x + 1][playerPos.y] == 2 && (set[playerPos.x + 2][playerPos.y] != 1 &&
			set[playerPos.x + 2][playerPos.y] != 2))
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
		else if (set[playerPos.x + 1][playerPos.y] == 5 &&
			(set[playerPos.x + 2][playerPos.y] != 1 && set[playerPos.x + 2][playerPos.y] != 2))
		{
			set[playerPos.x + 1][playerPos.y] = 6;
			numGoals++;
			if (set[playerPos.x + 2][playerPos.y] == 3)
			{
				set[playerPos.x + 2][playerPos.y] = 5;
				numGoals--;
			}
			if (set[playerPos.x + 2][playerPos.y] == 0)
			{
				set[playerPos.x + 2][playerPos.y] = 2;
			}

			resetTile(playerPos.x, playerPos.y);
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
		else if (set[playerPos.x - 1][playerPos.y] == 2 && (set[playerPos.x - 2][playerPos.y] != 1 &&
			set[playerPos.x - 2][playerPos.y] != 2))
		{
			if (set[playerPos.x - 2][playerPos.y] == 0)
			{
				set[playerPos.x - 2][playerPos.y] = 2;
				if (set[playerPos.x - 1][playerPos.y] == 2)
					set[playerPos.x - 1][playerPos.y] = 0;
			}
			else if (set[playerPos.x - 2][playerPos.y] == 3)
			{
				set[playerPos.x - 2][playerPos.y] = 5;
				numGoals--;
				if (set[playerPos.x - 1][playerPos.y] == 2)
					set[playerPos.x - 1][playerPos.y] = 0;
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
		else if (set[playerPos.x - 1][playerPos.y] == 5 &&
			(set[playerPos.x - 2][playerPos.y] != 1 && set[playerPos.x - 2][playerPos.y] != 2))
		{
			set[playerPos.x - 1][playerPos.y] = 6;
			numGoals++;
			if (set[playerPos.x - 2][playerPos.y] == 3)
			{
				set[playerPos.x - 2][playerPos.y] = 5;
				numGoals--;
			}
			if (set[playerPos.x - 2][playerPos.y] == 0)
			{
				set[playerPos.x - 2][playerPos.y] = 2;
			}

			resetTile(playerPos.x, playerPos.y);
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
		else if (set[playerPos.x][playerPos.y - 1] == 2 && (set[playerPos.x][playerPos.y - 2] != 1 &&
			set[playerPos.x][playerPos.y - 2] != 2))
		{

			if (set[playerPos.x][playerPos.y - 2] == 0)
			{
				set[playerPos.x][playerPos.y - 2] = 2;
				if (set[playerPos.x][playerPos.y - 1] == 2)
					set[playerPos.x][playerPos.y - 1] = 0;
			}
			else if (set[playerPos.x][playerPos.y - 2] == 3)
			{
				set[playerPos.x][playerPos.y - 2] = 5;
				numGoals--;
				if (set[playerPos.x][playerPos.y - 1] == 2)
					set[playerPos.x][playerPos.y - 1] = 0;
			}

			resetTile(playerPos.x, playerPos.y);

			if (set[playerPos.x][playerPos.y - 1] == 0)
				set[playerPos.x][playerPos.y - 1] = 4;
			if (set[playerPos.x][playerPos.y - 1] == 3)
				set[playerPos.x][playerPos.y - 1] = 6;
			playerPos.y--;
			if (!map.load("gfx/UpdatedTileSet.png", sf::Vector2u(64, 64), set, 11, 11))
				return;
		}
		else if (set[playerPos.x][playerPos.y - 1] == 5 &&
			(set[playerPos.x][playerPos.y - 2] != 1 && set[playerPos.x][playerPos.y - 2] != 2))
		{
			set[playerPos.x][playerPos.y - 1] = 6;
			numGoals++;
			if (set[playerPos.x][playerPos.y - 2] == 3)
			{
				set[playerPos.x][playerPos.y - 2] = 5;
				numGoals--;
			}
			if (set[playerPos.x][playerPos.y - 2] == 0)
			{
				set[playerPos.x][playerPos.y - 2] = 2;
			}

			resetTile(playerPos.x, playerPos.y);
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
		else if (set[playerPos.x][playerPos.y + 1] == 2 && (set[playerPos.x][playerPos.y + 2] != 1 &&
			set[playerPos.x][playerPos.y + 2] != 2))
		{

			if (set[playerPos.x][playerPos.y + 2] == 0)
			{
				set[playerPos.x][playerPos.y + 2] = 2;
				if (set[playerPos.x][playerPos.y + 1] == 2)
					set[playerPos.x][playerPos.y + 1] = 0;
			}
			else if (set[playerPos.x][playerPos.y + 2] == 3)
			{
				set[playerPos.x][playerPos.y + 2] = 5;
				numGoals--;
				if (set[playerPos.x][playerPos.y + 1] == 2)
					set[playerPos.x][playerPos.y + 1] = 0;
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
		else if (set[playerPos.x][playerPos.y + 1] == 5 &&
			(set[playerPos.x][playerPos.y + 2] != 1 && set[playerPos.x][playerPos.y + 2] != 2))
		{
			set[playerPos.x][playerPos.y + 1] = 6;
			numGoals++;
			if (set[playerPos.x][playerPos.y + 2] == 3)
			{
				set[playerPos.x][playerPos.y + 2] = 5;
				numGoals--;
			}
			if (set[playerPos.x][playerPos.y + 2] == 0)
			{
				set[playerPos.x][playerPos.y + 2] = 2;
			}

			resetTile(playerPos.x, playerPos.y);
			playerPos.y++;
			if (!map.load("gfx/UpdatedTileSet.png", sf::Vector2u(64, 64), set, 11, 11))
				return;
		}
		break;
	}

	//check for level complete
	if (numGoals <= 0)
	{
		numLevel++;
		ui[0].setString("Level: " + to_string(numLevel));
		nextLevel();
	}
}

void Game::draw(VirtualScreen& screen)
{
	screen.draw(map);
	screen.draw(noLevels);
	if (level.initialize(numLevel, genOrNo))
	screen.draw(ui[0]);
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

void Game::pause()
{

}

void Game::resume()
{

}

void Game::event(sf::Time elapsed, sf::Event a_event)
{
	if (a_event.type == sf::Event::KeyPressed)
	{
		if (a_event.key.code == sf::Keyboard::BackSpace)
			game.changeState(std::unique_ptr<GameState>(new Menu(game, font)));
		if (a_event.key.code == sf::Keyboard::R)
			nextLevel();
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
	}
}
