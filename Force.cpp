#include "Force.h"
#include "RigidBody.h"

Force::Force(glm::vec3 forceVector, ForceMode forceMode) :
	forceVector(forceVector), forceMode(forceMode)
{
}

const glm::vec3& Force::GetForceVector() {
	return forceVector;
}

void Force::SetForceVector(glm::vec3 forceVector) {
	this->forceVector = forceVector;
}

void Force::ApplyForce(RigidBody* rigidBody) {
	rigidBody->SetVelocity(rigidBody->GetVelocity() + forceVector * WorldTimer::phys_fdt());
}
