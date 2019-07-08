#include "Menu.h"

#include <memory>
#include <iostream>

#include "Game.h"
Menu::Menu(StateManager& a_game, sf::Font& a_font) :
	GameState(a_game),
	font(a_font)
{
	text.setFont(font);
	text.setString("MAIN MENU");
	text.setCharacterSize(50);
	text.setFillColor(sf::Color::Red);
	text.setPosition(210, 300);

	pressSpace.setFont(font);
	pressSpace.setString("(Press Space)");
	pressSpace.setCharacterSize(20);
	pressSpace.setFillColor(sf::Color::Red);
	pressSpace.setPosition(290, 450);
}

Menu::~Menu()
{

}

void Menu::pause()
{

}

void Menu::resume()
{

}

void Menu::event(sf::Time elapsed, sf::Event a_event)
{
	if (a_event.type == sf::Event::KeyPressed)
	{
		if (a_event.key.code == sf::Keyboard::Space)
		{
			std::cout << "Frame time: " << elapsed.asMilliseconds() << std::endl;

			game.changeState(
				std::unique_ptr<GameState>(new Game(game,font)));
		}
	}
}

void Menu::update(sf::Time elapsed, int playerInp)
{

}

void Menu::draw(VirtualScreen& screen)
{
	screen.draw(text);
	screen.draw(pressSpace);
}