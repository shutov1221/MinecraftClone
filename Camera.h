#pragma once

#include "Window.h"
#include "ViewFrustum.h"
#include "IWatcher.h"
#include "MovableObject.h"

#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtc/type_ptr.hpp"

class Camera : public MovableObject, public IWatcher
{
public:

	Camera(glm::vec3 position, float fov, float near, float far) :
		MovableObject(position), fov(fov), near(near), far(far)
	{
		viewFrustum = new ViewFrustum;
	}

	Camera(glm::vec3 position, float speed, float fov, float near, float far) :
		MovableObject(position, speed), fov(fov), near(near), far(far)
	{
		viewFrustum = new ViewFrustum;
	}

	ViewFrustum* GetViewFrustum() const;
	void Update();

	virtual glm::mat4 GetProjectionMatrix() override;
	virtual glm::mat4 GetViewMatrix() override;

private:
	float fov;
	float near;
	float far;
	ViewFrustum* viewFrustum;
};

