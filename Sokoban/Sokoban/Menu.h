#include <SFML/Graphics.hpp>
#include "Input.h"
#include <string.h>
#include "States.h"

class Menu
{
public:
	Menu(sf::RenderWindow* hwnd, Input* in);
	~Menu();

	void handleInput();
	void update();
	void render();
	GameState getState();


private:
	void beginDraw();
	void endDraw();
	sf::RenderWindow* window;
	Input* input;
	GameState state;
};