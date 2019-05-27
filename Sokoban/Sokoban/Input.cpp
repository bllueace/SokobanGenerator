#include "Input.h"
void Input::setKeyDown(int key)
{
	keys[key] = true;
}

void Input::setKeyUp(int key)
{
	keys[key] = false;
}

bool Input::isKeyDown(int key)
{
	return keys[key];
}
