#include "Menu.h"

#include <memory>
#include <iostream>

#include "Game.h"
#include "LevelGenerator.h"
Menu::Menu(StateManager& a_game, sf::Font& a_font) :
	GameState(a_game),
	font(a_font)
{
	menuBackground1.loadFromFile("gfx/MainMenu.png");
	bgr1.setTexture(&menuBackground1);
	bgr1.setSize(sf::Vector2f(720, 704));

	for (int i = 0; i < MAX_NUMBER; i++)
	{
		menu[i].setCharacterSize(30);
	}

	menu[0].setFont(font);
	menu[0].setFillColor(sf::Color::Blue);
	menu[0].setString("Play");
	menu[0].setCharacterSize(50);
	menu[0].setPosition(sf::Vector2f(WIDTH / 2 - 50, HEIGHT / (MAX_NUMBER_OF_ITEMS + 1) * 1));

	menu[1].setFont(font);
	menu[1].setFillColor(sf::Color::Red);
	menu[1].setString("Generate");
	menu[1].setPosition(sf::Vector2f(WIDTH / 2 - 50, HEIGHT / (MAX_NUMBER_OF_ITEMS + 1) * 1.5));

	menu[2].setFont(font);
	menu[2].setFillColor(sf::Color::Red);
	menu[2].setString("Credits");
	menu[2].setPosition(sf::Vector2f(WIDTH / 2 - 50, HEIGHT / (MAX_NUMBER_OF_ITEMS + 1) * 2));

	menu[3].setFont(font);
	menu[3].setFillColor(sf::Color::Red);
	menu[3].setString("Exit");
	menu[3].setPosition(sf::Vector2f(WIDTH / 2 - 50, HEIGHT / (MAX_NUMBER_OF_ITEMS + 1) * 2.5));

	selectedItem = 0;
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
		//if (a_event.key.code == sf::Keyboard::Enter)
			//game.changeState(std::unique_ptr<GameState>(new Game(game, font)));
		//if(a_event.key.code == sf::Keyboard::R)
			//game.changeState(std::unique_ptr<GameState>(new LevelGenerator(game, font)));
		if (a_event.key.code == sf::Keyboard::Down)
			MoveDown();
		if (a_event.key.code == sf::Keyboard::Up)
			MoveUp();
		if (a_event.key.code == sf::Keyboard::Enter)
		{
			switch (getPressedItem())
			{
			default:
				break;
			case 0:
				//std::cout << "Play button has been pressed" << std::endl;
				game.changeState(std::unique_ptr<GameState>(new Game(game, font)));
				break;
			case 1:
				//std::cout << "Generate button has been pressed" << std::endl;
				game.changeState(std::unique_ptr<GameState>(new LevelGenerator(game, font)));
				break;
			case 2:
				std::cout << "Credits button has been pressed" << std::endl;
				break;
			case 3:
				//quit the game and delete all current levels
				std::string command = "del /Q ";
				std::string path = "levels\\*.txt";
				system(command.append(path).c_str());
				exit(EXIT_FAILURE);
				break;
			}
		}
	}

}

void Menu::update(sf::Time elapsed, int playerInp)
{

}

void Menu::draw(VirtualScreen& screen)
{
	screen.draw(bgr1);

	for (int i = 0; i < MAX_NUMBER_OF_ITEMS; i++)
	{
		screen.draw(menu[i]);
	}
}

void Menu::MoveUp()
{
	if (selectedItem - 1 >= 0)
	{
		menu[selectedItem].setFillColor(sf::Color::Red);
		menu[selectedItem].setCharacterSize(30);
		selectedItem--;
		menu[selectedItem].setFillColor(sf::Color::Blue);
		menu[selectedItem].setCharacterSize(50);
	}
}

void Menu::MoveDown()
{
	if (selectedItem + 1 < MAX_NUMBER_OF_ITEMS)
	{
		menu[selectedItem].setFillColor(sf::Color::Red);
		menu[selectedItem].setCharacterSize(30);
		selectedItem++;
		menu[selectedItem].setFillColor(sf::Color::Blue);
		menu[selectedItem].setCharacterSize(50);
	}
}
