#pragma once
#include "Renderer.h"

class LightBlockRenderer : Renderer
{
public:
	LightBlockRenderer(Camera* camera, Shader* shader);

	~LightBlockRenderer();

	virtual void Render(void* mesh, unsigned int primitive) override;
};

