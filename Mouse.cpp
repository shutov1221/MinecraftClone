#include "Mouse.h"

double Mouse::x = 0.0f;
double Mouse::y = 0.0f;
double Mouse::dx = 0.0f;
double Mouse::dy = 0.0f;

bool Mouse::IsKeyPressed(MouseButton key) {
	std::vector<MouseButton>::iterator it = std::find(_Keys.begin(), _Keys.end(), key);
	return it != _Keys.end();
}

void Mouse::SetKeyPressed(MouseButton key) {
	if (!IsKeyPressed(key)) {
		_Keys.push_back(key);
	}
}

void Mouse::SetKeyReleased(MouseButton key) {
	if (IsKeyPressed(key)) {
		std::vector<MouseButton>::iterator it = std::find(_Keys.begin(), _Keys.end(), key);
		_Keys.erase(it);
	}
}
