#include "BlockRenderer.h"

BlockRenderer::BlockRenderer(Camera* camera) :
	Renderer(camera)
{
}

BlockRenderer::BlockRenderer(Camera* camera, Shader* shader) : 
	Renderer(camera, shader)
{
}

BlockRenderer::~BlockRenderer() {
}

void BlockRenderer::Render(void * mesh, unsigned int primitive) {
	if (shader != nullptr) {
		shader->setMat4("model", camera->GetModelMatrix());
		shader->setMat4("view", camera->GetViewMatrix());
		shader->setMat4("projection", camera->GetProjectionMatrix());

		static_cast<Mesh<32>*>(mesh)->Draw(primitive);
	}
}
