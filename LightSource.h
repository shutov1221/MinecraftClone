#pragma once

#include "MovableObject.h"
#include "IWatcher.h"
#include "Window.h"

struct LightSource : public MovableObject
{
	LightSource(glm::vec3 position, float near, float far) :
		MovableObject(position), color({ 1.0f, 1.0f, 1.0f }), power(1.0f), near(near), far(far)
	{
	}

	LightSource(glm::vec3 position, glm::vec3 color, float near, float far) :
		MovableObject(position), color(color), power(1.0f), near(near), far(far)
	{
	}

	LightSource(glm::vec3 position, glm::vec3 color, float power, float near, float far) :
		MovableObject(position), color(color), power(power), near(near), far(far)
	{
	}

	glm::vec3 color;
	float power;
	float near;
	float far;
};

