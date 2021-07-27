#pragma once
#include "WorldConstants.h"

#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtc/type_ptr.hpp"

class Object
{
public:
	Object();
	Object(glm::vec3 position);

	void Rotate(float yaw, float pitch, float roll);
	void Translate(float dx, float dy, float dz);

	void Rotate(glm::vec3 rotation);
	void Translate(glm::vec3 translation);

	const glm::mat4& GetModelMatrix();

	void SetPosition(glm::vec3 position);
	const glm::vec3& GetPosition();

	glm::vec3 GetVP(const glm::vec3& normal) const;

	virtual void Update() {};

protected:
	glm::vec3 position;
	glm::mat4 modelMatrix = glm::mat4(1.0f);
};

