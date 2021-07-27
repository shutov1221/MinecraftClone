#include "Rectangle.h"
#include "RectangleMeshBuilder.h"

Rectangle::Rectangle(glm::vec3 topLeft, glm::vec3 color, float xLength, float zLength) :
	Object(glm::vec3(topLeft.x + xLength / 2.0f, topLeft.y, topLeft.z + zLength / 2.0f)), 
	Displayed<4>(new RectangleMeshBuilder(this)),
	color(color),
	bottomRight(glm::vec3(topLeft.x + xLength, topLeft.y, topLeft.z + zLength)),
	topLeft(topLeft), xLength(xLength), zLength(zLength)
{

}

void Rectangle::SetLengthZ(float zLength) 
{
	this->zLength = zLength;
	Update();
}

void Rectangle::SetLengthX(float xLength) 
{
	this->xLength = xLength;
	Update();
}

void Rectangle::SetPosition(glm::vec3 position) 
{
	this->position = position;
	Update();
}

void Rectangle::Update() 
{
	topLeft = glm::vec3(position.x - xLength / 2.0f, position.y, position.z - zLength / 2.0f);
	bottomRight = glm::vec3(position.x + xLength / 2.0f, position.y, position.z + zLength / 2.0f);
}