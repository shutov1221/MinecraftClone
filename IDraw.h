#pragma once
#include "Renderer.h"

class IDraw
{
public:
	virtual void Draw(Renderer* renderer) = 0;
};

