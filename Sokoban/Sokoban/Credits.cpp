#include "Credits.h"

#include <memory>
#include <iostream>

#include "Game.h"
#include "LevelGenerator.h"

Credits::Credits(StateManager& a_game, sf::Font& a_font) :
	GameState(a_game),
	font(a_font)
{
	menuBackground1.loadFromFile("gfx/credits.png");
	bgr1.setTexture(&menuBackground1);
	bgr1.setSize(sf::Vector2f(720, 704));
}

Credits::~Credits()
{

}

void Credits::pause()
{

}

void Credits::resume()
{

}

void Credits::event(sf::Time elapsed, sf::Event a_event)
{
	if (a_event.type == sf::Event::KeyPressed)
	{
		if (a_event.key.code == sf::Keyboard::Backspace)
		{
			game.changeState(std::unique_ptr<GameState>(new Menu(game, font)));

		}
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

void Credits::update(sf::Time elapsed, int playerInp)
{

}

void Credits::draw(VirtualScreen& screen)
{
	screen.draw(bgr1);
}
