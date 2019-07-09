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
	sf::Text startGame;
	sf::Text generateLevels;
	sf::Text goToCreddits;
	sf::Text quitGame;
	sf::RectangleShape bgr1;
	sf::Texture menuBackground1;
};

#endif // MENU_H