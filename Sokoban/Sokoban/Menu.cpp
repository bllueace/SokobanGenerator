#include "Menu.h"

Menu::Menu(sf::RenderWindow* hwnd, Input* in)
{

	window = hwnd;
	input = in;
	state = GameState::MENU;
}
Menu::~Menu()
{
}

GameState Menu::getState()
{
	return state;
}

void Menu::handleInput()
{
	if (input->isKeyDown(sf::Keyboard::Return))
	{
		input->setKeyUp(sf::Keyboard::Return);
		state = GameState::LEVEL;
	}
	else
	{
		state = GameState::MENU;
	}
}

void Menu::update()
{
}

void Menu::render()
{
	beginDraw();
	endDraw();
}

void Menu::beginDraw()
{
	window->clear();
}

void Menu::endDraw()
{
	window->display();
}