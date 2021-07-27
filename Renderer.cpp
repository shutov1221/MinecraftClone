#include "Renderer.h"

Renderer::Renderer() {
	camera = nullptr;
	shader = nullptr;
}

Renderer::Renderer(Camera* camera) :
	camera(camera)
{
	shader = nullptr;
}

Renderer::Renderer(Shader* shader) :
	shader(shader)
{
	camera = nullptr;
}

Renderer::Renderer(Camera* camera, Shader* shader) : 
	camera(camera), 
	shader(shader)
{
}

Renderer::~Renderer() {
	//delete shader;
}

void Renderer::useShader(Shader* shader) {
	this->shader = shader;
	shader->use();
}

void Renderer::Clear() {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}
