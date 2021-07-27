#pragma once
#include "Collider.h"
#include "World.h"

class BlockWorldCollider : public Collider
{
public:
	BlockWorldCollider() = default;

	virtual void ApplyNormalForce(RigidBody* rigidBody, Force& force, Renderer* renderer) override;
	BoundingBox GetSweptBroadphaseBox(RigidBody* rigidBody);
};

