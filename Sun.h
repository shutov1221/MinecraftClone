#pragma once
#include "LightSource.h"
#include "Window.h"
#include "Camera.h"

class Sun : public LightSource, public IWatcher
{

public:
	Sun(glm::vec3 position, float near, float far, Camera* camera);
	Sun(glm::vec3 position, glm::vec3 color, float near, float far, Camera* camera);
	Sun(glm::vec3 position, glm::vec3 color, float power, float near, float far, Camera* camera);

	float viewSize = 100.0f;

	void MoveAroundHemiSphere(float dalpha, float dbeta);
	void SetAlphaAngle(float alpha);
	void SetBetaAngle(float beta);
	void Update();

	virtual glm::mat4 GetProjectionMatrix() override;
	virtual glm::mat4 GetViewMatrix() override;
private:
	float x = 0.0f;
	float z = 0.0f;
	float y = 4 * CHUNK_Y;
	float alpha;
	float beta;
	Camera* camera;
};

