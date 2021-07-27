#pragma once
#include "Camera.h"
#include "Shader.h"
#include "Mesh.h"
#include "utils.h"
#include <vector>

class Renderer
{
public:
	Renderer();
	Renderer(Camera* camera);
	Renderer(Shader* shader);
	Renderer(Camera* camera, Shader* shader);
	virtual ~Renderer();

	virtual void Render(void * mesh, unsigned int primitive) = 0;

	void useShader(Shader* shader);

	void Clear();

protected:
	Camera* camera;
	Shader* shader;
};

