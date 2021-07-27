#include "MovableObject.h"

MovableObject::MovableObject() :
	Object(glm::vec3(0.0f)), velocity(0.0f), rotation(1.0f), speed(0.0f)
{
	acceleration = glm::vec3(0.0f);

	up = glm::vec3(0.0f, 1.0f, 0.0f);
	right = glm::vec3(1.0f, 0.0f, 0.0f);
	front = glm::vec3(0.0f, 0.0f, -1.0f);

	baseUp = up;
	baseRight = right;
	baseFront = front;

	UpdateBaseVectors();
}

MovableObject::MovableObject(glm::vec3 position, float speed) :
	Object(position), speed(speed)
{
	acceleration = glm::vec3(0.0f);

	up = glm::vec3(0.0f, 1.0f, 0.0f);
	right = glm::vec3(1.0f, 0.0f, 0.0f);
	front = glm::vec3(0.0f, 0.0f, -1.0f);

	baseUp = up;
	baseRight = right;
	baseFront = front;

	UpdateBaseVectors();
}

MovableObject::MovableObject(glm::vec3 position, glm::vec3 start_velocity) :
	Object(position), velocity(start_velocity)
{
	acceleration = glm::vec3(0.0f);

	up = glm::vec3(0.0f, 1.0f, 0.0f);
	right = glm::vec3(1.0f, 0.0f, 0.0f);
	front = glm::vec3(0.0f, 0.0f, -1.0f);

	baseUp = up;
	baseRight = right;
	baseFront = front;

	UpdateBaseVectors();
}

MovableObject::MovableObject(glm::vec3 position) :
	Object(position), velocity(0.0f), rotation(1.0f), speed(0.0f)
{
	acceleration = glm::vec3(0.0f);

	up = glm::vec3(0.0f, 1.0f, 0.0f);
	right = glm::vec3(1.0f, 0.0f, 0.0f);
	front = glm::vec3(0.0f, 0.0f, -1.0f);

	baseUp = up;
	baseRight = right;
	baseFront = front;

	UpdateBaseVectors();
}

MovableObject::MovableObject(glm::vec3 position, glm::vec3 start_velocity, glm::mat4 rotation) :
	Object(position), velocity(start_velocity), rotation(rotation), speed(0.0f)
{
	acceleration = glm::vec3(0.0f);

	up = glm::vec3(0.0f, 1.0f, 0.0f);
	right = glm::vec3(1.0f, 0.0f, 0.0f);
	front = glm::vec3(0.0f, 0.0f, -1.0f);

	baseUp = up;
	baseRight = right;
	baseFront = front;

	UpdateBaseVectors();
}

MovableObject::MovableObject(glm::vec3 position, glm::vec3 start_velocity, glm::mat4 rotation, float speed) :
	Object(position), velocity(start_velocity), rotation(rotation), speed(speed)
{
	acceleration = glm::vec3(0.0f);

	up = glm::vec3(0.0f, 1.0f, 0.0f);
	right = glm::vec3(1.0f, 0.0f, 0.0f);
	front = glm::vec3(0.0f, 0.0f, -1.0f);

	baseUp = up;
	baseRight = right;
	baseFront = front;

	UpdateBaseVectors();
}

void MovableObject::Rotate(float yaw, float pitch, float roll) {
	rotation = glm::mat4(1.0f);

	rotation = glm::rotate(rotation, pitch, glm::vec3(0, 1, 0));

	UpdateBaseVectors();

	rotation = glm::rotate(rotation, yaw, glm::vec3(1, 0, 0));
	rotation = glm::rotate(rotation, roll, glm::vec3(0, 0, 1));

	UpdateVectors();
}

void MovableObject::UpdateVectors() {
	front = glm::normalize(glm::vec3(rotation * glm::vec4(0, 0, -1, 1)));
	right = glm::normalize(glm::vec3(rotation * glm::vec4(1, 0, 0, 1)));
	up = glm::normalize(glm::vec3(rotation * glm::vec4(0, 1, 0, 1)));
}

void MovableObject::UpdateBaseVectors() {
	baseFront = glm::normalize(glm::vec3(rotation * glm::vec4(0, 0, -1, 1)));
	baseRight = glm::normalize(glm::vec3(rotation * glm::vec4(1, 0, 0, 1)));
}

const glm::vec3& MovableObject::GetUpVector() {
	return up;
}

const glm::vec3& MovableObject::GetRightVector() {
	return right;
}

const glm::vec3& MovableObject::GetFrontVector() {
	return front;
}

const glm::vec3& MovableObject::GetBaseUpVector() {
	return baseUp;
}

const glm::vec3& MovableObject::GetBaseFrontVector() {
	return baseFront;
}

const glm::vec3& MovableObject::GetBaseRightVector() {
	return baseRight;
}

const glm::vec3& MovableObject::GetVelocity() {
	return velocity;
}

void MovableObject::SetVelocity(glm::vec3 velocity) {
	this->velocity = velocity;
}

const glm::vec3& MovableObject::GetAcceleration() {
	return acceleration;
}

void MovableObject::SetAcceleration(glm::vec3 acceleration) {
	this->acceleration = acceleration;
}
