#pragma once

#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtc/type_ptr.hpp"

class IWatcher
{
public:
	virtual glm::mat4 GetProjectionMatrix() = 0;
	virtual glm::mat4 GetViewMatrix() = 0;
};