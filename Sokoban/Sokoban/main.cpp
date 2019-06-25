#include "Game.h"
#include "Input.h"
#include "Menu.h"
int main()
{
	sf::RenderWindow window(sf::VideoMode(704, 704), "Sokoban");
	Input input;
	Game game(&window, &input);
	Menu menu(&window, &input);

	GameState state = GameState::LEVEL;

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
						game.runSolution();
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
			game.render();
			state = game.getState();
			break;
		}

	}
	return 0;
}