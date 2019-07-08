#ifndef GAMESTATE_H
#define GAMESTATE_H

#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include "StateManager.h"

class GameState
{
public:
	GameState(StateManager& a_game);
	virtual ~GameState();

	// Lifetime management functions
	virtual void pause() = 0;
	virtual void resume() = 0;

	// State loop functions, called in this order
	// Note: elapsed times are measured from the last frame, not as totals
	virtual void event(sf::Time elapsed, sf::Event a_event) = 0;
	virtual void update(sf::Time elapsed, int playerInp) = 0;
	virtual void draw(VirtualScreen& screen) = 0;

protected:
	StateManager& game;
};

#endif