#include "Keyboard.h"
#include <iostream>

bool Keyboard::JustKeyPressed(int key) {
	std::vector<int>::iterator it = std::find(_Keys.begin(), _Keys.end(), key);
	return it != _Keys.end() && frames[key] == current;
}

bool Keyboard::IsKeyPressed(int key) {
	std::vector<int>::iterator it = std::find(_Keys.begin(), _Keys.end(), key);
	return it != _Keys.end();
}

bool Keyboard::IsKeyReleased(int key) {
	bool result = false;
	if (frames[key] == -1) 
	{
		result = true;
		frames[key] = 0;
	}

	return result;
}

void Keyboard::SetKeyPressed(int key) {
	if (!IsKeyPressed(key)) {
		_Keys.push_back(key);
	}
}

void Keyboard::SetKeyReleased(int key) {
	if (IsKeyPressed(key)) {
		std::vector<int>::iterator it = std::find(_Keys.begin(), _Keys.end(), key);
		_Keys.erase(it);
	}
}

void Keyboard::frameHandler(uint* _frames, uint current) {
	this->current = current;
	this->frames = _frames;
}