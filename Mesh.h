#pragma once
#include <glad/glad.h>
#include <stdlib.h>
#include <vector>
#include <array>

#include "utils.h"

template<int T>
class Mesh
{
public:
	Mesh(uint* attributes) {
		Init(attributes);
		glGenVertexArrays(1, &VAO);
		glGenBuffers(1, &VBO);
		glGenBuffers(1, &EBO);
	}

	~Mesh() {

		glDeleteVertexArrays(1, &VAO);
		glDeleteBuffers(1, &VBO);
		glDeleteBuffers(1, &EBO);
	}

	void Init(uint* attributes) {
		if (attributes != nullptr) {
			this->attributes = attributes;

			for (uint i = 0; attributes[i]; i++) {
				vertex_size += attributes[i];
			}
		}
	}

	void Draw(unsigned int primitive) {
		if (primitive == GL_LINES) {
			glLineWidth(15.0f);
		}
		glBindVertexArray(VAO);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
		glDrawElements(primitive, indices_size, GL_UNSIGNED_INT, 0);
		glBindVertexArray(0);
	}

	void BindVertexArray(Vertices<T>& buffer, std::vector<int>& indices) {
		glBindVertexArray(VAO);
			glBindBuffer(GL_ARRAY_BUFFER, VBO);
				v_size = buffer.size() * (T / vertex_size);

				glBufferData(GL_ARRAY_BUFFER, buffer.size() * T * sizeof(Vertex), &buffer.front(), GL_STATIC_DRAW);

				int offset = 0;
				for (uint i = 0; attributes[i]; i++) {
					int size = attributes[i];
					glEnableVertexAttribArray(i);
					glVertexAttribPointer(i, size, GL_FLOAT, GL_FALSE, vertex_size * sizeof(float), (GLvoid*)(offset * sizeof(float)));
					offset += size;
				}
			glBindBuffer(GL_ARRAY_BUFFER, 0);

			glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
				glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(int), &indices.front(), GL_STATIC_DRAW);
				indices_size = indices.size();
			glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

		glBindVertexArray(0);
	}

	void UpdateVertexArray(Vertices<T>& buffer) {
		glBindVertexArray(VAO);
		glBindBuffer(GL_ARRAY_BUFFER, VBO);
		glBufferSubData(GL_ARRAY_BUFFER, 0, buffer.size() * T * sizeof(float), &buffer.front());
	}

private:
	unsigned int VAO;
	unsigned int VBO;
	unsigned int EBO;

	uint* attributes;

	int vertex_size = 0;
	int indices_size = 0;

	size_t v_size;
};

