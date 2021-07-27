#include "Sun.h"

Sun::Sun(glm::vec3 position, float near, float far, Camera* camera) :
	LightSource(position, near, far), camera(camera)
{
	alpha = 0.0f;
	beta = 90.0f;
}

Sun::Sun(glm::vec3 position, glm::vec3 color, float near, float far, Camera* camera) :
	LightSource(position, color, near, far), camera(camera)
{
	alpha = 0.0f;
	beta = 90.0f;
}

Sun::Sun(glm::vec3 position, glm::vec3 color, float power, float near, float far, Camera* camera) :
	LightSource(position, color, power, near, far), camera(camera)
{
	alpha = 0.0f;
	beta = 90.0f;
}

glm::mat4 Sun::GetProjectionMatrix() {
	return glm::ortho(-viewSize, viewSize,
		-viewSize * Window::GetAspect(), viewSize * Window::GetAspect(), near, far);
}

glm::mat4 Sun::GetViewMatrix() {
	auto& cameraPos = camera->GetPosition();
	float pos_x = cameraPos.x + x;
	float pos_z = cameraPos.z + z;
	position = glm::vec3(pos_x, y, pos_z);
	return glm::lookAt(position, glm::vec3(cameraPos.x, 0.0f, cameraPos.z), glm::vec3(0.0, 1.0, 0.0));
}

void Sun::MoveAroundHemiSphere(float dalpha, float dbeta) {
	 
	float r = 4 * CHUNK_Y;

	alpha += dalpha;
	beta += dbeta;

	//std::cout << "Alpha = " << alpha << std::endl;
	//std::cout << "Beta = " << beta << std::endl;

	if (alpha > 180.0f) {
		alpha = 180.0f;
	}

	if (alpha < 0.0f) {
		alpha = 0.0f;
	}

	if (beta > 360.0f) {
		beta = 0.0f;
	}

	if (beta < 0.0f) {
		beta = 360.0f;
	}

	float x = 0.0f, y = 0.0f, z = 0.0f;
	auto& cameraPos = camera->GetPosition();

	x = r * sin(glm::radians(beta)) * cos(glm::radians(alpha));
	y = r * sin(glm::radians(beta)) * sin(glm::radians(alpha));
	z = r * cos(glm::radians(beta));

	/*std::cout << cameraPos.x << std::endl;
	std::cout << cameraPos.y << std::endl;
	std::cout << cameraPos.z << std::endl;*/

	//position = glm::vec3(cameraPos.x + x, y, cameraPos.z + z);
	this->x = x;
	this->z = z;
	this->y = y;
}

void Sun::SetAlphaAngle(float alpha) {
	this->alpha = alpha;
}

void Sun::SetBetaAngle(float beta) {
	this->beta = beta;
}

void Sun::Update() {
	auto& cameraPos = camera->GetPosition();
	int r = 4 * CHUNK_Y;
	float x, y, z;

	x = r * cos(glm::radians(beta)) * cos(glm::radians(alpha));
	z = r * cos(glm::radians(beta)) * sin(glm::radians(alpha));
	y = r * sin(glm::radians(beta));

	position = glm::vec3(cameraPos.x + x, cameraPos.y + y, z);
}

