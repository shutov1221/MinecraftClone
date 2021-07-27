#pragma once
#include "Window.h"
#include <string>
#include "Mouse.h"
#include "Keyboard.h"
#include "utils.h"

class EventsKeys
{
public:
	int Initialize();
	~EventsKeys();
	void PullKeysEvents();

	static uint* _frames;
	static uint _current;
};

