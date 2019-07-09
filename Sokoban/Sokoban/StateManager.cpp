#include "StateManager.h"
#include <iostream>
#include "GameState.h"


StateManager::StateManager(sf::RenderWindow& a_window, VirtualScreen& a_screen) :
	window(a_window),
	screen(a_screen),
	screenSprite(screen.getTexture()),
	screenView(sf::Vector2f(0, 0), sf::Vector2f(screen.getSize().x,
		screen.getSize().y))
{
	// The maintainAspectRatio() method requires the sprite in question to be
	// centered
	screenSprite.setOrigin(float(screenSprite.getTextureRect().width / 2.0),
		float(screenSprite.getTextureRect().height / 2.0));

	screenSprite.setTextureRect(sf::IntRect(0,
		0,
		screen.getSize().x,
		screen.getSize().y));

	maintainAspectRatio(screenView, window);
	running = true;
}


StateManager::~StateManager()
{
	// Empty the stack of GameStates and properly destroy the GameStates
	while (!states.empty())
		states.pop();

	window.close();
}

void StateManager::loop()
{
	sf::Event a_event;
	sf::Time elapsed;

	// Just in case the Game was constructed long before loop() started
	clock.restart();

	while (running)
	{
		playerMove = 0;

		// Gets the elapsed time and simultaneously resets the Clock
		elapsed = clock.restart();
		while (window.pollEvent(a_event))
		{
			window.setKeyRepeatEnabled(false);

			if (a_event.type == sf::Event::Closed)
			{
				window.close();
			}
			switch (a_event.type)
			{
			case sf::Event::KeyPressed:
				if (a_event.type == sf::Event::KeyPressed)
				{
					//player movement
					if (a_event.key.code == sf::Keyboard::Down)
						playerMove = 1;
					else if (a_event.key.code == sf::Keyboard::Up)
						playerMove = 2;
					else if (a_event.key.code == sf::Keyboard::Left)
						playerMove = 3;
					else if (a_event.key.code == sf::Keyboard::Right)
						playerMove = 4;

					if (a_event.key.code == sf::Keyboard::Escape)
						window.close();
				}
				//pressed = true;
				break;
			}
			event(elapsed, a_event);
		}
		update(elapsed,playerMove);
		draw();
	}
}

void StateManager::changeState(std::unique_ptr<GameState> state)
{
	if (!states.empty())
		states.pop();

	pushState(std::move(state));
}

/// Push a GameState onto the stack
void StateManager::pushState(std::unique_ptr<GameState> state)
{
	if (!states.empty())
		states.top()->pause();

	// GameStates start paused and must be resumed
	state->resume();

	states.push(std::move(state));
}

/// Pop a GameState off of the stack
void StateManager::popState()
{
	if (!states.empty())
	{
		states.pop();
		states.top()->resume(); // Resume previous state
	}
}

//~--- Lifetime methods

/// Signals the intention to exit the game at the next opportunity
void StateManager::quit()
{
	running = false;
}

// Handles each event for both the Game and the current GameState. Note: this
// method may run any number of times per frame
void StateManager::event(sf::Time elapsed, sf::Event a_event)
{
	// Ensures that the virtual screen is kept at the proper size and
	// aspect ratio within the RenderWindow
	if (a_event.type == sf::Event::Resized)
		maintainAspectRatio(screenView, window);

	// Call event() on the current state
	if (!states.empty())
		states.top()->event(elapsed, a_event);
}

// Handles the per-frame update of the Game and its current GameState
void StateManager::update(sf::Time elapsed, int playerInp)
{
	// Call update() on the Game itself
	//update(elapsed,playerInp);

	// Call update() on the current state
	if (!states.empty())
		states.top()->update(elapsed,playerInp);
}

/// Draws both the Game and it's current GameState
void StateManager::draw()
{
	screen.clear();

	// Pass any GameStates our virtual screen to draw on. They will have no
	// knowledge of the actual window.
	if (!states.empty())
		states.top()->draw(screen);

	// Draw our virtual screen onto our real window. The view established by
	// maintainAspectRatio() will ensure proper size, ratio, and positioning
	window.clear();
	screen.display();
	window.draw(screenSprite);
	window.display();
}

void StateManager::maintainAspectRatio(sf::View& view, sf::RenderWindow& window)
{
	// sf::View.getSize() returns a Vector2f, this is float division
	float viewRatio = view.getSize().x / view.getSize().y;
	float winRatio = ((float)window.getSize().x) / window.getSize().y;

	float viewWidthFrac;
	float viewHeightFrac;

	// Determine the ratios of viewport size to window size which will
	// maintain the view ports aspect ratio
	if (winRatio > viewRatio)
	{
		// If the view is "narrower" in ratio than the window
		viewWidthFrac = viewRatio / winRatio;
		viewHeightFrac = 1.0f; // It's height will match the window's height
	}
	else
	{
		// If the view is "shorter" in ratio than the window
		viewWidthFrac = 1.0f; // It's width will match the windows width
		viewHeightFrac = winRatio / viewRatio;
	}

	// Find where the top left corner of the viewport should be in order to
	// center it 
	float xPos = 0.5f - (viewWidthFrac / 2.0f);
	float yPos = 0.5f - (viewHeightFrac / 2.0f);

	// Setting the viewport allows us to map a view to a window at a specific
	// location and proportion

	view.setViewport(sf::FloatRect(xPos, yPos, viewWidthFrac, viewHeightFrac));
	//view.rotate(180);
	window.setView(view);
}