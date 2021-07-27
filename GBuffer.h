#pragma once

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "Window.h"
#include "utils.h"

class GBuffer
{
public:
	GBuffer();
	~GBuffer();
	void Create();

	uint GetGPosition();
	uint GetGAlbedo();
	uint GetGNormals();
	uint GetGDepth();

	void Update();

	uint Get_ID();

private:
	void GenGPositionTexture();
	void GenGAlbedoTexture();
	void GenGDepthTexture();
	void GenGNormalsTexture();

	void GenTextures();

	uint gBuffer;

	uint gPosition;
	uint gNormal;
	uint rboDepth;
	uint gAlbedo;

	int screenHeight;
	int screenWidth;
};

