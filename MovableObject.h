#pragma once
#include "Object.h"

class MovableObject : public Object
{
public:
	MovableObject();
	MovableObject(glm::vec3 position);
	MovableObject(glm::vec3 position, float speed);
	MovableObject(glm::vec3 position, glm::vec3 start_velocity);
	MovableObject(glm::vec3 position, glm::vec3 start_velocity, glm::mat4 rotation);
	MovableObject(glm::vec3 position, glm::vec3 start_velocity, glm::mat4 rotation, float speed);

	void Rotate(float yaw, float pitch, float roll);

	const glm::vec3& GetVelocity();
	void SetVelocity(glm::vec3 velocity);

	const glm::vec3& GetAcceleration();
	void SetAcceleration(glm::vec3 acceleration);
	
	const glm::vec3& GetUpVector();
	const glm::vec3& GetRightVector();
	const glm::vec3& GetFrontVector();

	const glm::vec3& GetBaseUpVector();
	const glm::vec3& GetBaseFrontVector();
	const glm::vec3& GetBaseRightVector();

protected:
	glm::vec3 up;
	glm::vec3 right;
	glm::vec3 front;

	glm::vec3 baseUp;
	glm::vec3 baseFront;
	glm::vec3 baseRight;

	glm::mat4 rotation;
	glm::vec3 velocity;
	glm::vec3 acceleration;

	glm::mat4 modelMatrix;

	void UpdateVectors();
	void UpdateBaseVectors();

private:
	float speed;
};

