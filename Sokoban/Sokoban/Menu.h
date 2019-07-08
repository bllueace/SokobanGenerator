#ifndef MENU_H
#define MENU_H

#include "GameState.h"

class Menu : public GameState
{
public:
	Menu(StateManager& a_game, sf::Font& font);
	virtual ~Menu();

	void pause();
	void resume();

	void event(sf::Time elapsed, sf::Event a_event);
	void update(sf::Time elapsed, int playerInp);
	void draw(VirtualScreen& screen);

private:
	sf::Font& font;
	sf::Text text;
	sf::Text pressSpace;
};

#endif // MENU_H