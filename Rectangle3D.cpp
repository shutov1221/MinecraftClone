#include "Rectangle3D.h"

Rectangle3D::Rectangle3D(glm::vec3 topLeftBack, float xLength, float yLength, float zLength) :
	Rectangle(topLeftBack, xLength, zLength), yLength(yLength)
{
	this->position.y = topLeftBack.y + yLength / 2.0f;
}

void Rectangle3D::SetLengthY(float yLength) 
{
	this->yLength = yLength;
	Update();
}

void Rectangle3D::Update() 
{
	topLeft = glm::vec3(position.x - xLength / 2.0f, position.y - yLength / 2.0f, position.z - zLength / 2.0f);
	bottomRight = glm::vec3(position.x + xLength / 2.0f, position.y + yLength / 2.0f, position.z + zLength / 2.0f);
}