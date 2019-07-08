#include <chrono>
using std::chrono::duration_cast;
using std::chrono::milliseconds;
typedef std::chrono::steady_clock the_clock;

#include <memory>
#include <iostream>
#include "StateManager.h"
#include "Menu.h"
#include "Input.h"
#include "Game.h"
#define SCREEN_WIDTH 704
#define SCREEN_HEIGHT 704
//int main()
//{
//	sf::RenderWindow window(sf::VideoMode(SCREEN_WIDTH, SCREEN_HEIGHT), "Sokoban");
//	VirtualScreen screen(SCREEN_WIDTH, SCREEN_HEIGHT);
//
//	StateManager game(window, screen);
//
//	int playerMove = 0;
//	//DeltaTime
//	sf::Clock clock;
//	float deltaTime;
//
//	window.setKeyRepeatEnabled(false);
//	bool pressed = false;
//	while (window.isOpen())
//	{
//		sf::Event event;
//		while (window.pollEvent(event))
//		{
//			if (event.type == sf::Event::Closed)
//			{
//				window.close();
//			}
//
//			switch (event.type)
//			{
//			case sf::Event::KeyPressed:
//				if (event.type == sf::Event::KeyPressed)
//				{
//					if(event.key.code == sf::Keyboard::R)
//						//game.initialiseLevel();
//					if (event.key.code == sf::Keyboard::Space)
//					{
//						the_clock::time_point start = the_clock::now();
//						//game.initialiseLevel();
//						//game.runSolution();
//						the_clock::time_point end = the_clock::now();
//						int time_taken = duration_cast<milliseconds>(end - start).count();
//						std::cout << "Generating complete level took: " << time_taken << "ms." << std::endl;
//					}
//
//					//player movement
//					if (event.key.code == sf::Keyboard::Down)
//						playerMove = 1;
//					else if (event.key.code == sf::Keyboard::Up)
//						playerMove = 2;
//					else if (event.key.code == sf::Keyboard::Left)
//						playerMove = 3;
//					else if (event.key.code == sf::Keyboard::Right)
//						playerMove = 4;
//
//				}
//				//pressed = true;
//				break;
//			}
//
//		}
//
//		deltaTime = clock.restart().asSeconds();
//		sf::Font font;
//		if (!font.loadFromFile("font/arial.ttf"))
//		{
//			return -1;
//		}
//		game.pushState(std::unique_ptr<GameState>(new Menu(game, font)));
//
//		game.loop();
//		
//	}
//	return 0;
//}

int main()
{
	sf::RenderWindow window(sf::VideoMode(SCREEN_WIDTH, SCREEN_WIDTH), "Sokoban");
	VirtualScreen screen(SCREEN_WIDTH, SCREEN_WIDTH);

	StateManager game(window, screen);
	window.setKeyRepeatEnabled(false);
	window.setFramerateLimit(60);
	Input input;
	int playerInp = 0;
	sf::Font font;
	if (!font.loadFromFile("font/arial.ttf"))
	{
		return -1;
	}

	//while (window.isOpen())
	//{
	//	sf::Event event;
	//	while (window.pollEvent(event))
	//	{
	//		if (event.type == sf::Event::Closed)
	//		{
	//			window.close();
	//		}

	//		switch (event.type)
	//		{
	//		case sf::Event::KeyPressed:
	//			if (event.type == sf::Event::KeyPressed)
	//			{
	//				//player movement
	//				if (event.key.code == sf::Keyboard::Down)
	//					playerInp = 1;
	//				else if (event.key.code == sf::Keyboard::Up)
	//					playerInp = 2;
	//				else if (event.key.code == sf::Keyboard::Left)
	//					playerInp = 3;
	//				else if (event.key.code == sf::Keyboard::Right)
	//					playerInp = 4;

	//			}
	//			//pressed = true;
	//			break;
	//		}
	//	}
		game.pushState(std::unique_ptr<GameState>(new Game(game, font)));

		game.loop();

		return 0;
	//}
}