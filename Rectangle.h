#pragma once
#include "MovableObject.h"
#include "glm/glm.hpp"
#include "Displayed.h"

class RectangleMeshBuilder;

class Rectangle : public Object, public Displayed<4>
{
public:
	Rectangle(glm::vec3 topLeft, glm::vec3 color, float xLength, float zLength);

	void SetLengthZ(float zLength);
	void SetLengthX(float xLength);
	void SetPosition(glm::vec3 position);
	virtual void Update() override;

protected:
	glm::vec3 topLeft;
	glm::vec3 bottomRight;
	glm::vec3 color;
	float xLength;
	float zLength;

	friend class RectangleMeshBuilder;
};

