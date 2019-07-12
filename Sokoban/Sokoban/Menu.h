#ifndef MENU_H
#define MENU_H

#include "GameState.h"
#define MAX_NUMBER_OF_ITEMS 4
#define WIDTH 704
#define HEIGHT 704
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

	void MoveUp();
	void MoveDown();
	int getPressedItem() { return selectedItem; }
private:
	sf::Font& font;
	sf::RectangleShape bgr1;
	sf::Texture menuBackground1;

	int selectedItem;
	sf::Text menu[MAX_NUMBER_OF_ITEMS];
};

#endif // MENU_H