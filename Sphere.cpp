#include "Sphere.h"

Sphere::Sphere(float r, glm::vec3 position, glm::vec3 color, int stacks, int slices) :
	r(r), MovableObject(position), color(color), stacks(stacks), slices(slices)
{
	mesh = new Mesh<1>(new uint[4]{ 3, 2, 3, 0 });
}

Sphere::~Sphere() {
    delete mesh;
}

void Sphere::Draw(Renderer* renderer) {
    MakeMesh();
    renderer->Render(mesh, GL_TRIANGLES);
}

void Sphere::SetPosition(glm::vec3 newPosition) {
    position = newPosition;
}

void Sphere::SetColor(glm::vec3 newColor) {
    color = newColor;
}

void Sphere::SetStacks(int newStacks) {
    stacks = newStacks;
}

void Sphere::SetSlices(int newSlices) {
    slices = newSlices;
}

void Sphere::MakeMesh() {
    vertices.clear();
    indices.clear();
    vertices.shrink_to_fit();
    indices.shrink_to_fit();

    for (int i = 0; i <= stacks; ++i) {

        float V = i / (float)stacks;
        float phi = V * glm::pi <float>();

        for (int j = 0; j <= slices; ++j) {

            float U = j / (float)slices;
            float theta = U * (glm::pi <float>() * 2);

            float x = cosf(theta) * sinf(phi);
            float y = cosf(phi);
            float z = sinf(theta) * sinf(phi);

            vertices.push_back({ Vertex(glm::vec3(x * r + position.x, y * r + position.y, z * r + position.z), glm::vec2(0.0f, 0.0f),  glm::vec3(color.x, color.y, color.z)) });
        }
    }

    for (int i = 0; i < slices * stacks + slices; ++i) {

        indices.push_back(i);
        indices.push_back(i + slices + 1);
        indices.push_back(i + slices);

        indices.push_back(i + slices + 1);
        indices.push_back(i);
        indices.push_back(i + 1);
    }

    mesh->BindVertexArray(vertices, indices);
}
