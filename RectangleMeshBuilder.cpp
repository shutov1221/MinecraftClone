#include "RectangleMeshBuilder.h"

RectangleMeshBuilder::RectangleMeshBuilder(Rectangle* rectangle) :
	MeshBuilder<4>(new uint[4]{ 3, 2, 3, 0 }), rectangle(rectangle)
{
}

RectangleMeshBuilder::~RectangleMeshBuilder()
{
}

void RectangleMeshBuilder::BuildMesh()
{
	vertices = {
		{
			Vertex(rectangle->topLeft,     glm::vec2(0.0f, 0.0f), rectangle->color),
			Vertex(glm::vec3(rectangle->bottomRight.x, rectangle->topLeft.y, rectangle->topLeft.z),     glm::vec2(0.0f, 0.0f), rectangle->color),
			Vertex(rectangle->bottomRight, glm::vec2(0.0f, 0.0f), rectangle->color),
			Vertex(glm::vec3(rectangle->topLeft.x, rectangle->topLeft.y, rectangle->bottomRight.z),     glm::vec2(0.0f, 0.0f), rectangle->color),
		}
	};

	indices = {
		0, 1, 2, 2, 3, 0
	}
}