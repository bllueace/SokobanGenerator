#pragma once
class Input {
private:

public:
	void setKeyDown(int key);
	void setKeyUp(int key);
	bool isKeyDown(int key);

private:
	bool keys[256]{ false };
};