#pragma once
#include "Renderer.h"
#include "Mesh.h"

class ScreenRenderer : public Renderer
{
public:
	ScreenRenderer();
	ScreenRenderer(Shader* shader);
	virtual void Render(void* mesh, unsigned int primitive) override;
	~ScreenRenderer();

private:
	void BindVertices();
	uint* attributes;
	Mesh<4>* mesh;
};

