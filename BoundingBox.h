#pragma once
#include "glm/glm.hpp"
#include <iostream>
#include "Mesh.h"
#include "Renderer.h"
#include "Rectangle3D.h"

class BoundingBox : public Rectangle3D
{
public:
	BoundingBox(float size)
	

};

extern bool AABB(BoundingBox box_1, BoundingBox box_2);
extern float SweptAABB(BoundingBox box1, BoundingBox box2, glm::vec3 vel1, float& normalx, float& normaly, float& normalz);


/*struct BoundingBox
{
	BoundingBox(float size) :
		width(size), height(size), length(size)
	{
		position = glm::vec3(0.0f);

		mesh = new Mesh<4>(new uint[4]{ 3, 2, 3, 0 });

		minX = (-width / 2.0f);
		maxX = ( width / 2.0f);
		minY = (-height / 2.0f);
		maxY = ( height / 2.0f);
		minZ = (-length / 2.0f);
		maxZ = ( length / 2.0f);
	}

	BoundingBox(float width, float height, float length) :
		width(width), height(height), length(length)
	{
		position = glm::vec3(0.0f);

		mesh = new Mesh<4>(new uint[4]{ 3, 2, 3, 0 });

		minX = (-width  / 2.0f );
		maxX = ( width  / 2.0f );
		minY = (-height / 2.0f);
		maxY = ( height / 2.0f);
		minZ = (-length / 2.0f);
		maxZ = ( length / 2.0f);
	}

	void Update(glm::vec3 position) {
		this->position = position;
		minX = position.x - width / 2.0f;
		maxX = position.x + width / 2.0f;
		minY = position.y - height / 2.0f;
		maxY = position.y + height / 2.0f;
		minZ = position.z - length / 2.0f;
		maxZ = position.z + length / 2.0f;
	}

	void MakeMesh(glm::vec3 color) {
		vertices.clear();
		indices.clear();
		vertices.shrink_to_fit();
		indices.shrink_to_fit();

		vertices =
		{
			// Top face
			{
				Vertex(glm::vec3(maxX + 0.0f, maxY + 0.0f, maxZ + 0.0f), glm::vec2(0.0f, 0.0f), glm::vec3(color.x, color.y, color.z)),
				Vertex(glm::vec3(maxX + 0.0f, maxY + 0.0f, minZ - 0.0f), glm::vec2(0.0f, 0.0f), glm::vec3(color.x, color.y, color.z)),
				Vertex(glm::vec3(minX - 0.0f, maxY + 0.0f, minZ - 0.0f), glm::vec2(0.0f, 0.0f), glm::vec3(color.x, color.y, color.z)),
				Vertex(glm::vec3(minX - 0.0f, maxY + 0.0f, maxZ + 0.0f), glm::vec2(0.0f, 0.0f), glm::vec3(color.x, color.y, color.z)),
			},

			{
				Vertex(glm::vec3(maxX + 0.0f, maxY + 0.0f, maxZ + 0.0f), glm::vec2(0.0f, 0.0f), glm::vec3(color.x, color.y, color.z)),
				Vertex(glm::vec3(maxX + 0.0f, minY - 0.0f, maxZ + 0.0f), glm::vec2(0.0f, 0.0f), glm::vec3(color.x, color.y, color.z)),
				Vertex(glm::vec3(maxX + 0.0f, minY - 0.0f, minZ - 0.0f), glm::vec2(0.0f, 0.0f), glm::vec3(color.x, color.y, color.z)),
				Vertex(glm::vec3(maxX + 0.0f, maxY + 0.0f, minZ - 0.0f), glm::vec2(0.0f, 0.0f), glm::vec3(color.x, color.y, color.z)),
			},
				
			{
				Vertex(glm::vec3(minX - 0.0f, maxY + 0.0f, maxZ + 0.0f), glm::vec2(0.0f, 0.0f), glm::vec3(color.x, color.y, color.z)),
				Vertex(glm::vec3(minX - 0.0f, minY - 0.0f, maxZ + 0.0f), glm::vec2(0.0f, 0.0f), glm::vec3(color.x, color.y, color.z)),
				Vertex(glm::vec3(minX - 0.0f, minY - 0.0f, minZ - 0.0f), glm::vec2(0.0f, 0.0f), glm::vec3(color.x, color.y, color.z)),
				Vertex(glm::vec3(minX - 0.0f, maxY + 0.0f, minZ - 0.0f), glm::vec2(0.0f, 0.0f), glm::vec3(color.x, color.y, color.z)),
			},
				
			{
				Vertex(glm::vec3(maxX + 0.0f, maxY + 0.0f, minZ - 0.0f), glm::vec2(0.0f, 0.0f), glm::vec3(color.x, color.y, color.z)),
				Vertex(glm::vec3(maxX + 0.0f, minY - 0.0f, minZ - 0.0f), glm::vec2(0.0f, 0.0f), glm::vec3(color.x, color.y, color.z)),
				Vertex(glm::vec3(minX - 0.0f, minY - 0.0f, minZ - 0.0f), glm::vec2(0.0f, 0.0f), glm::vec3(color.x, color.y, color.z)),
				Vertex(glm::vec3(minX - 0.0f, maxY + 0.0f, minZ - 0.0f), glm::vec2(0.0f, 0.0f), glm::vec3(color.x, color.y, color.z)),
			},
				
			{
				Vertex(glm::vec3(maxX + 0.0f, maxY + 0.0f, maxZ + 0.0f), glm::vec2(0.0f, 0.0f), glm::vec3(color.x, color.y, color.z)),
				Vertex(glm::vec3(maxX + 0.0f, minY - 0.0f, maxZ + 0.0f), glm::vec2(0.0f, 0.0f), glm::vec3(color.x, color.y, color.z)),
				Vertex(glm::vec3(minX - 0.0f, minY - 0.0f, maxZ + 0.0f), glm::vec2(0.0f, 0.0f), glm::vec3(color.x, color.y, color.z)),
				Vertex(glm::vec3(minX - 0.0f, maxY + 0.0f, maxZ + 0.0f), glm::vec2(0.0f, 0.0f), glm::vec3(color.x, color.y, color.z)),
			},
				
			{
				Vertex(glm::vec3(maxX + 0.0f, minY - 0.0f, minZ - 0.0f), glm::vec2(0.0f, 0.0f), glm::vec3(color.x, color.y, color.z)),
				Vertex(glm::vec3(maxX + 0.0f, minY - 0.0f, maxZ + 0.0f), glm::vec2(0.0f, 0.0f), glm::vec3(color.x, color.y, color.z)),
				Vertex(glm::vec3(minX - 0.0f, minY - 0.0f, maxZ + 0.0f), glm::vec2(0.0f, 0.0f), glm::vec3(color.x, color.y, color.z)),
				Vertex(glm::vec3(minX - 0.0f, minY - 0.0f, minZ - 0.0f), glm::vec2(0.0f, 0.0f), glm::vec3(color.x, color.y, color.z)),
			}
			
		};

		indices =
		{
			0, 1, 1, 2, 2, 3, 3, 0,
			4, 5, 5, 6, 6, 7, 7, 4,
			8, 9, 9, 10, 10, 11, 11, 8,
			12, 13, 13, 14, 14, 15, 15, 12,
			16, 17, 17, 18, 18, 19, 19, 16,
			20, 21, 21, 22, 22, 23, 23, 20
		};

		mesh->BindVertexArray(vertices, indices);
	}

	void Draw(Renderer* renderer, glm::vec3 color) {
		MakeMesh(color);
		renderer->Render(mesh, GL_LINES);
	}

	glm::vec3 GetPosition() {
		return position;
	}

	glm::vec3 position;

	float width;
	float height;
	float length;

	float minX;
	float maxX;
	float minY;
	float maxY;
	float minZ;
	float maxZ;

	Mesh<4>* mesh;

	std::vector<std::array<Vertex, 4>> vertices;
	std::vector<int> indices;

};*/