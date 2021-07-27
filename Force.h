#pragma once

#include "WorldTimer.h"

#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtc/type_ptr.hpp"

class RigidBody;

enum class ForceMode
{
	Force,
	Acceleration,
	Impulse,
	VelocityChange
};

class Force
{
public:
	Force(glm::vec3 forceVector, ForceMode forceMode);

	void ApplyForce(RigidBody* rigidBody);

	const glm::vec3& GetForceVector();
	void SetForceVector(glm::vec3 forceVector);

private:
	ForceMode forceMode;
	glm::vec3 forceVector;
};

