#include "ScreenRenderer.h"

ScreenRenderer::ScreenRenderer() {
    attributes = new uint[4]{ 3, 2, 3, 0 };
    mesh = new Mesh<4>(attributes);
    BindVertices();
}

ScreenRenderer::ScreenRenderer(Shader* shader) :
    Renderer(shader)
{
    attributes = new uint[4]{ 3, 2, 3, 0 };
    mesh = new Mesh<4>(attributes);
    BindVertices();
}

ScreenRenderer::~ScreenRenderer() {
    delete[] attributes;
    delete mesh;
}

void ScreenRenderer::BindVertices() {
    std::vector<std::array<Vertex, 4>> screenVertices =
    {
        {
            Vertex(glm::vec3(-1.0f,  1.0f, 0.0f), glm::vec2(0.0f, 1.0f), glm::vec3(0.0f, 0.0f, 0.0f)),
            Vertex(glm::vec3(-1.0f, -1.0f, 0.0f), glm::vec2(0.0f, 0.0f), glm::vec3(0.0f, 0.0f, 0.0f)),
            Vertex(glm::vec3( 1.0f,  1.0f, 0.0f), glm::vec2(1.0f, 1.0f), glm::vec3(0.0f, 0.0f, 0.0f)),
            Vertex(glm::vec3( 1.0f, -1.0f, 0.0f), glm::vec2(1.0f, 0.0f), glm::vec3(0.0f, 0.0f, 0.0f)),
        }
    };

    std::vector<int> indices = {
        0, 1, 2, 1, 3, 2
    };

    if (mesh != nullptr) { 
        mesh->BindVertexArray(screenVertices, indices);
    }
}

void ScreenRenderer::Render(void* mesh, unsigned int primitive) {
    if (shader != nullptr) {
        this->mesh->Draw(primitive);
    }
}

