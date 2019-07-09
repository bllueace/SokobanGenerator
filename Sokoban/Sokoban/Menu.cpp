#include "Menu.h"

#include <memory>
#include <iostream>

#include "Game.h"
#include "LevelGenerator.h"
Menu::Menu(StateManager& a_game, sf::Font& a_font) :
	GameState(a_game),
	font(a_font)
{
	startGame.setFont(font);
	startGame.setString("Press 'ENTER' To start Game");
	startGame.setCharacterSize(20);
	startGame.setFillColor(sf::Color::Red);
	startGame.setPosition(250, 200);

	generateLevels.setFont(font);
	generateLevels.setString("Press 'R' to go generate level");
	generateLevels.setCharacterSize(20);
	generateLevels.setFillColor(sf::Color::Red);
	generateLevels.setPosition(250, 250);

	goToCreddits.setFont(font);
	goToCreddits.setString("Press 'C' to go to credits");
	goToCreddits.setCharacterSize(20);
	goToCreddits.setFillColor(sf::Color::Red);
	goToCreddits.setPosition(250, 300);

	quitGame.setFont(font);
	quitGame.setString("Press 'ECS' to quit game");
	quitGame.setCharacterSize(20);
	quitGame.setFillColor(sf::Color::Red);
	quitGame.setPosition(250, 350);

	menuBackground1.loadFromFile("gfx/MainMenu.png");
	bgr1.setTexture(&menuBackground1);
	bgr1.setSize(sf::Vector2f(720, 704));
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
		if (a_event.key.code == sf::Keyboard::Enter)
			game.changeState(std::unique_ptr<GameState>(new Game(game, font)));
		if(a_event.key.code == sf::Keyboard::R)
			game.changeState(std::unique_ptr<GameState>(new LevelGenerator(game, font)));
	}

}

void Menu::update(sf::Time elapsed, int playerInp)
{

}

void Menu::draw(VirtualScreen& screen)
{
	screen.draw(bgr1);
	screen.draw(startGame);
	screen.draw(generateLevels);
	screen.draw(goToCreddits);
	screen.draw(quitGame);
}