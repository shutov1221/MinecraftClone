#pragma once
#include "RigidBody.h"
#include <array>

class Collider
{
public:
	Collider() = default;
	virtual ~Collider() {}

	virtual void ApplyNormalForce(RigidBody* rigidBody, Force& force, Renderer* rendere) = 0;
};

