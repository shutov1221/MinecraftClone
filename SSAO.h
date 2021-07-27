#pragma once
#include "GBuffer.h"
#include "ShaderCollection.h"
#include "Camera.h"
#include "Renderer.h"
#include "ScreenRenderer.h"
#include "World.h"

#include <vector>
#include <random>

#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtc/type_ptr.hpp"

class SSAO
{
public:
	SSAO(Camera* camera);
	~SSAO();

	void Init();
	void Update();
	void Enable();
	void Disable();

	uint CalculateSSAO(Renderer* geometry, Renderer* screen);

private:
	void GeometricPass(Renderer* geometry);
	void SSAO_Pass(Renderer* screen);
	void SSAO_Blur_Pass(Renderer* screen);

	void GenColorBuffer();
	void GenColorBufferBlur();
	void GenNoiseTexture();

	void fillKernel();

	std::vector<glm::vec3> ssaoKernel;
	std::vector<glm::vec3> ssaoNoise;
	std::uniform_real_distribution<GLfloat> randomFloats;
	std::default_random_engine generator;

	uint ssaoFBO = 0; 
	uint ssaoBlurFBO = 0;
	uint ssaoColorBuffer = 0;
	uint ssaoColorBufferBlur = 0;
	uint noiseTexture = 0;

	//Shaders

	Shader* shaderGeometryPass;
	Shader* shaderSSAO;
	Shader* shaderSSAOBlur;

	GBuffer* gBuff;

	Camera* camera;

	int screenHeight;
	int screenWidth;

	bool enabled;
};

static float lerp(float a, float b, float f)
{
	return a + f * (b - a);
}
