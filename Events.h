#pragma once
#include "Window.h"
#include "EventsKeys.h"
#include "WindowEvents.h"


class Events
{
public:
	Events();
	~Events();

	void Initialize();
	void PullEvents();

private:
	EventsKeys* eKeys;
	WindowEvents* eWindow;
};

