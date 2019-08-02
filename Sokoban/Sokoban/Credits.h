#ifndef CREDITS_H
#define CREDITS_H

#include "GameState.h"
#define WIDTH 704
#define HEIGHT 704
class Credits : public GameState
{
public:
	Credits(StateManager& a_game, sf::Font& font);
	virtual ~Credits();

	void pause();
	void resume();

	void event(sf::Time elapsed, sf::Event a_event);
	void update(sf::Time elapsed, int playerInp);
	void draw(VirtualScreen& screen);
private:
	sf::Font& font;
	sf::RectangleShape bgr1;
	sf::Texture menuBackground1;
};

#endif // CREDITS_H