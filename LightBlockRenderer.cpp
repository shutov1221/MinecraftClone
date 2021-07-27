#include "LightBlockRenderer.h"

LightBlockRenderer::LightBlockRenderer(Camera* camera, Shader* shader) :
	Renderer(camera, shader)
{
}

LightBlockRenderer::~LightBlockRenderer() {
}

void LightBlockRenderer::Render(void * mesh, unsigned int primitive) {
	if (shader != nullptr) {
		shader->use();

		shader->setMat4("model", camera->GetModelMatrix());
		shader->setMat4("view", camera->GetViewMatrix());
		shader->setMat4("projection", camera->GetProjectionMatrix());

		static_cast<Mesh<18>*>(mesh)->Draw(primitive);
	}
}
