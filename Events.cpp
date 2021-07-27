#include "Events.h"

Events::Events()
{
}

Events::~Events() {
	delete eKeys;
	delete eWindow;
}

void Events::Initialize() {
	eKeys = new EventsKeys();
	eWindow = new WindowEvents();

	eKeys->Initialize();
	eWindow->Initialize();
}

void Events::PullEvents() {
	eKeys->PullKeysEvents();
	eWindow->PullWindowEvents();
}


