#include "Game.h"
#include "Input.h"
#include "Menu.h"
#include <chrono>
using std::chrono::duration_cast;
using std::chrono::milliseconds;
typedef std::chrono::steady_clock the_clock;
int main()
{
	sf::RenderWindow window(sf::VideoMode(704, 704), "Sokoban");
	Input input;
	Game game(&window, &input);
	Menu menu(&window, &input);

	GameState state = GameState::LEVEL;
	int playerMove = 0;
	//DeltaTime
	sf::Clock clock;
	float deltaTime;
	window.setKeyRepeatEnabled(false);
	bool pressed = false;
	while (window.isOpen())
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
			{
				window.close();
			}

			switch (event.type)
			{
			case sf::Event::KeyPressed:
				if (event.type == sf::Event::KeyPressed)
				{
					if(event.key.code == sf::Keyboard::R)
						game.initialiseLevel();
					if (event.key.code == sf::Keyboard::Space)
					{
						the_clock::time_point start = the_clock::now();
						//game.initialiseLevel();
						game.runSolution();
						the_clock::time_point end = the_clock::now();
						int time_taken = duration_cast<milliseconds>(end - start).count();
						std::cout << "Generating complete level took: " << time_taken << "ms." << std::endl;
					}

					//player movement
					if (event.key.code == sf::Keyboard::Right)
					{
						playerMove = 1;
					}


				}
				//pressed = true;
				break;


			}

		}

		deltaTime = clock.restart().asSeconds();
		switch (state)
		{
		//case (GameState::MENU):
		//	menu.handleInput();
		//	menu.render();
		//	state = menu.getState();
		//	break;
		case(GameState::LEVEL):
			//game.handleInput();
			//game.update(playerMove);
			playerMove = 0;
			game.render();
			state = game.getState();
			break;
		}

	}
	return 0;
}