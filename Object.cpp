#include "Object.h"

Object::Object() :
	position(glm::vec3(0.0f))
{
}

Object::Object(glm::vec3 position) :
	position(position)
{
}

void Object::SetPosition(glm::vec3 position) 
{
	this->position = position;
	//Translate(position);
}

const glm::vec3& Object::GetPosition() {
	return position;
}

const glm::mat4& Object::GetModelMatrix() {
	return modelMatrix;
}

void Object::Rotate(float yaw, float pitch, float roll) {
	modelMatrix = glm::rotate(modelMatrix, pitch, glm::vec3(0, 1, 0));
	modelMatrix = glm::rotate(modelMatrix, yaw, glm::vec3(1, 0, 0));
	modelMatrix = glm::rotate(modelMatrix, roll, glm::vec3(0, 0, 1));
}

void Object::Translate(float dx, float dy, float dz) {
	modelMatrix = glm::translate(modelMatrix, glm::vec3(dx, dy, dz));
}

void Object::Rotate(glm::vec3 rotation) {
	Rotate(rotation.x, rotation.y, rotation.z);
}

void Object::Translate(glm::vec3 translation) {
	Translate(translation.x, translation.y, translation.z);
}

glm::vec3 Object::GetVP(const glm::vec3& normal) const 
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