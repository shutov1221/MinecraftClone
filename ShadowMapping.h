#pragma once

#include "ShaderCollection.h"
#include "Sun.h"
#include "World.h"
#include "BlockRenderer.h"

class ShadowMapping
{
public:
	ShadowMapping(Sun* sun);
	~ShadowMapping();

	void Init();

	void Enable();
	void Disable();

	void SetShadowHeight(uint height);
	void SetShadowWidth(uint width);

	uint GetDepthMap(Renderer* renderer);

private:
	void Update();

	void GenDepthBuffer();
	void GenDepthTexture();

	void CalculateDepthTexture(Renderer* renderer);

	Shader* depthShader;

	int screenHeight;
	int screenWidth;

	Sun* sun;

	uint shadowHeight = 0;
	uint shadowWidth = 0;

	uint depthMapFBO = 0;
	uint depthMap = 0;

	bool enabled = true;

};