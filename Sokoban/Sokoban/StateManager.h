#ifndef STATEMANAGER_H
#define STATEMANAGER_H
#include <stack>
#include <memory>
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>

#include "VirtualScreen.h"

class GameState;

class StateManager
{
public:
	StateManager(sf::RenderWindow& a_window, VirtualScreen& a_screen);
	virtual ~StateManager();

	// Main loop method
	void loop();

	// State management methods
	void changeState(std::unique_ptr<GameState> state);
	void pushState(std::unique_ptr<GameState> state);
	void popState();
	void quit();

protected:
	sf::RenderWindow& window;
	VirtualScreen& screen;

private:
	void event(sf::Time elapsed, sf::Event a_event);
	void update(sf::Time elapsed, int playerInp);
	void draw();
	void maintainAspectRatio(sf::View& view, sf::RenderWindow& window);

	sf::Sprite screenSprite;
	sf::View screenView;

	std::stack<std::unique_ptr<GameState>> states;
	bool running;

	sf::Clock clock;

	int playerMove = 0;
};

#endif