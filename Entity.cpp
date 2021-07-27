#include "Entity.h"

Entity::Entity() 
	: position(0.0f, 0.0f, 0.0f), rotation(1.0f), velocity(0.0f, 0.0f, 0.0f), speed(0.0f)
{
	front = glm::vec3(0.0f, 0.0f, 1.0f);
	up = glm::vec3(0.0f, 1.0f, 0.0f);
	right = glm::vec3(1.0f, 0.0f, 0.0f);
	acceleration = glm::vec3(0.0f, 0.0f, 0.0f);

	updateBaseVectors();
}

Entity::Entity(glm::vec3 position) 
	: position(position), rotation(1.0f), velocity(0.0f, 0.0f, 0.0f), speed(0.0f)
{
	front = glm::vec3(0.0f, 0.0f, 1.0f);
	up =	glm::vec3(0.0f, 1.0f, 0.0f);
	right = glm::vec3(1.0f, 0.0f, 0.0f);
	acceleration = glm::vec3(0.0f, 0.0f, 0.0f);

	updateBaseVectors();
}

Entity::Entity(glm::vec3 position, glm::vec3 velocity)
	: position(position), rotation(1.0f), velocity(velocity), speed(0.0f)
{
	front = glm::vec3(0.0f, 0.0f, 1.0f);
	up =	glm::vec3(0.0f, 1.0f, 0.0f);
	right = glm::vec3(1.0f, 0.0f, 0.0f);
	acceleration = glm::vec3(0.0f, 0.0f, 0.0f);

	updateBaseVectors();
}


Entity::Entity(glm::vec3 position, glm::vec3 velocity, float speed)
	: position(position), rotation(1.0f), velocity(velocity), speed(speed)
{
	front = glm::vec3(0.0f, 0.0f, 1.0f);
	up = glm::vec3(0.0f, 1.0f, 0.0f);
	right = glm::vec3(1.0f, 0.0f, 0.0f);
	acceleration = glm::vec3(0.0f, 0.0f, 0.0f);

	updateBaseVectors();
}

Entity::~Entity() {}

void Entity::updateBaseVectors() {
	front = glm::normalize(glm::vec3(rotation * glm::vec4(0, 0, -1, 1)));
	right = glm::normalize(glm::vec3(rotation * glm::vec4(1, 0, 0, 1)));
	up =	glm::normalize(glm::vec3(rotation * glm::vec4(0, 1, 0, 1)));
}

glm::vec3& Entity::getCurrentPosition() {
	return position;
}

float Entity::getCurrentSpeed() {
	return speed;
}

void Entity::setNewSpeed(float speed) {
	this->speed = speed;
}

glm::vec3& Entity::getAcceleration() {
	return acceleration;
}

void Entity::rotate(float x, float y, float z) {
	rotation = glm::mat4(1.0f);

	rotation = glm::rotate(rotation, z, glm::vec3(0, 0, 1));
	rotation = glm::rotate(rotation, y, glm::vec3(0, 1, 0));
	rotation = glm::rotate(rotation, x, glm::vec3(1, 0, 0));

	updateBaseVectors();
}

void Entity::translate(float x, float y, float z) {
	//glm::v
}

void Entity::move(glm::vec3 direction, float time) {
	position += glm::vec3(rotation * glm::vec4(direction, 1.0)) * time * 150.0f;
}

glm::vec3 Entity::GetVP(const glm::vec3& normal) const
{
	glm::vec3 res = position;
	glm::vec3 dimensions = { CHUNK_X, CHUNK_Y, CHUNK_Z };

	if (normal.x > 0)
	{
		res.x += dimensions.x;
	}
	if (normal.y > 0)
	{
		res.y += dimensions.y;
	}
	if (normal.z > 0)
	{
		res.z += dimensions.z;
	}

	return res;
}

