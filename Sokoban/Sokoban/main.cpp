#include "Game.h"
#include "Input.h"
#include "Menu.h"
int main()
{
	sf::RenderWindow window(sf::VideoMode(640, 640), "Sokoban");
	Input input;
	Game game(&window, &input);
	Menu menu(&window, &input);

	GameState state = GameState::LEVEL;

	//DeltaTime
	sf::Clock clock;
	float deltaTime;

	while (window.isOpen())
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
			{
				window.close();
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
			game.handleInput();
			game.render();
			state = game.getState();
			break;
		}

	}
	return 0;
}