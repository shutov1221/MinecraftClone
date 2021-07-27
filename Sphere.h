#pragma once
#include "Mesh.h"
#include "Renderer.h"
#include "MovableObject.h"

#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtc/type_ptr.hpp"

class Sphere : public MovableObject
{
public:
	Sphere(float r, glm::vec3 position, glm::vec3 color, int stacks = 10, int slices = 10);
	~Sphere();
	void Draw(Renderer* renderer);

	void SetPosition(glm::vec3 newPosition);
	void SetColor(glm::vec3 newColor);
	void SetStacks(int newStacks);
	void SetSlices(int newSlices);

private:
	float r;
	int stacks;
	int slices;

	glm::vec3 color;

	std::vector<std::array<Vertex, 1>> vertices;
	std::vector<int> indices;

	Mesh<1>* mesh;

	void MakeMesh();
};

