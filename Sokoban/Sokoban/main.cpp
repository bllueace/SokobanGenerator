#include <memory>
#include <iostream>
#include "StateManager.h"
#include "Menu.h"
#include "Game.h"
#define SCREEN_WIDTH 704
#define SCREEN_HEIGHT 704

int main()
{
	sf::RenderWindow window(sf::VideoMode(SCREEN_WIDTH, SCREEN_WIDTH), "Sokoban");
	VirtualScreen screen(SCREEN_WIDTH, SCREEN_WIDTH);

	StateManager game(window, screen);
	window.setKeyRepeatEnabled(false);
	window.setFramerateLimit(60);
	int playerInp = 0;
	sf::Font font;
	if (!font.loadFromFile("font/SEVESBRG.ttf"))
	{
		return -1;
	}

	game.pushState(std::unique_ptr<GameState>(new Menu(game, font)));

	game.loop();

	return 0;

}