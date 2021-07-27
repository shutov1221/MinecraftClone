#pragma once

#include "glm/glm.hpp"

struct Vertex {
	Vertex(glm::vec3 position, glm::vec2 texCoords, glm::vec3 normal) :
		position(position), texCoords(texCoords), normal(normal)
	{
	}

	glm::vec3 position;
	glm::vec2 texCoords;
	glm::vec3 normal;
};