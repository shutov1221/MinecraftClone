#pragma once

#include "MovableObject.h"
#include "BoundingBox.h"
#include "Force.h"
#include <vector>

class Collider;

class RigidBody : public MovableObject
{
public:
	RigidBody(float mass, BoundingBox boundingBox, Collider* collider);
	RigidBody(glm::vec3 position, float mass, BoundingBox boundingBox, Collider* collider);
	RigidBody(glm::vec3 position, glm::vec3 start_velocity, float mass, BoundingBox boundingBox, Collider* collider);
	RigidBody(glm::vec3 position, glm::vec3 start_velocity, glm::mat4 rotation, float mass, BoundingBox boundingBox, Collider* collider);
	~RigidBody();

	float GetMass();
	void SetMass(float mass);

	const BoundingBox& GetBoundingBox();
	void SetBoundingBox(BoundingBox boundingBox);

	void AddForce(Force force);
	void AddForce(glm::vec3 forceVector, ForceMode forceMode);

	void SetOnGround(bool status);
	bool IsOnGround();

	void DrawBoundingBox(Renderer* renderer, glm::vec3 color);

	virtual void Update();

protected:
	std::vector<Force> forces;
	BoundingBox boundingBox;
	float mass;

	Collider* collider;
	Renderer* renderer;

	bool onGround = false;
};

