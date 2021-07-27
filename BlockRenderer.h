#pragma once
#include "Renderer.h"
#include "Mesh.h"

class BlockRenderer : public Renderer
{
public:
	BlockRenderer(Camera* camera);
	BlockRenderer(Camera* camera, Shader* shader);
	~BlockRenderer();

	virtual void Render(void* mesh, unsigned int primitive) override;
};

