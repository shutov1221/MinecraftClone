#include "WorldTimer.h"
#include <GLFW/glfw3.h>

double WorldTimer::lastFrameTime = 0.0;
double WorldTimer::currentTime = glfwGetTime();
double WorldTimer::_dt = 0.0;
double WorldTimer::physics_dt = 1.0f / 60.0f;

WorldTimer* WorldTimer::worldTimer = nullptr;

void WorldTimer::CreateClock() {
	if (worldTimer == nullptr) {
		worldTimer = new WorldTimer();
	}
}

WorldTimer::WorldTimer() {}

void WorldTimer::Update() {
	currentTime = glfwGetTime();
	_dt = currentTime - lastFrameTime;
	lastFrameTime = currentTime;
}

float WorldTimer::fdt() {
	return (float)_dt;
}

float WorldTimer::ftime() {
	return (float)currentTime;
}

double WorldTimer::dt() {
	return _dt;
}

double WorldTimer::phys_dt() {
	return physics_dt;
}

float WorldTimer::phys_fdt() {
	return float(physics_dt);
}

double WorldTimer::time() {
	return currentTime;
}