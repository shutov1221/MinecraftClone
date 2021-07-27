#pragma once
#include "Rectangle.h"

class Rectangle3D : public Rectangle
{
public:
	Rectangle3D(glm::vec3 topLeftBack, float xLength, float yLength, float zLength);

	void SetLengthY(float yLength);
	virtual void Update() override;

protected:
	float yLength;
};

