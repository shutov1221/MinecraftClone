#include "RigidBody.h"
#include "Collider.h"


RigidBody::RigidBody(float mass, BoundingBox boundingBox, Collider* collider) :
	mass(mass), boundingBox(boundingBox), collider(collider)
{
}

RigidBody::RigidBody(glm::vec3 position, float mass, BoundingBox boundingBox, Collider* collider) :
	MovableObject(position), mass(mass), boundingBox(boundingBox), collider(collider)
{
}

RigidBody::RigidBody(glm::vec3 position, glm::vec3 start_velocity, float mass, BoundingBox boundingBox, Collider* collider) :
	MovableObject(position, start_velocity), mass(mass), boundingBox(boundingBox), collider(collider)
{
}

RigidBody::RigidBody(glm::vec3 position, glm::vec3 start_velocity, glm::mat4 rotation, float mass, BoundingBox boundingBox, Collider* collider) :
	MovableObject(position, start_velocity, rotation), mass(mass), boundingBox(boundingBox), collider(collider)
{
}

RigidBody::~RigidBody() {
	delete collider;
}

void RigidBody::SetOnGround(bool status) {
	this->onGround = status;
}

bool RigidBody::IsOnGround() {
	return onGround;
}

float RigidBody::GetMass() {
	return mass;
}

void RigidBody::SetMass(float mass) {
	this->mass = mass;
}

const BoundingBox& RigidBody::GetBoundingBox() {
	return boundingBox;
}

void RigidBody::SetBoundingBox(BoundingBox boundingBox) {
	this->boundingBox = boundingBox;
}

void RigidBody::AddForce(Force force) {
	/*auto& forceVector = force.GetForceVector();
	if (forceVector == glm::vec3(0.0f, 0.0f, 0.0f)) {
		return;
	}

	collider->ApplyNormalForce(this, force);*/

	forces.push_back(force);
}

void RigidBody::AddForce(glm::vec3 forceVector, ForceMode forceMode) {
	forces.emplace_back(forceVector, forceMode);
}

void RigidBody::DrawBoundingBox(Renderer* renderer, glm::vec3 color) {
	this->renderer = renderer;
	boundingBox.Draw(renderer, color);
}

void RigidBody::Update() {
	for (auto& force : forces) {
		force.ApplyForce(this);
	}

	baseUp = glm::vec3(0.0f, up.y, 0.0f);
	baseFront = glm::vec3(front.x, 0.0f, front.z);
	baseRight = glm::vec3(right.x, 0.0f, right.z);

	forces.clear();
	forces.shrink_to_fit();
}
