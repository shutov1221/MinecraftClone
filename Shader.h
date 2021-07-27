#pragma once
#include <glad/glad.h>
#include <string>
#include <fstream>
#include <sstream>
#include <iostream>

#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtc/type_ptr.hpp"

class Shader
{
public:
	Shader(GLint id);
	virtual ~Shader();

	GLint get_id();

	void setBool(const std::string& name, bool value) const;
	void setInt(const std::string& name, int value) const;
	void setFloat(const std::string& name, float value) const;
	void setMat4(const std::string& name, const glm::mat4 matrix);
	void setVec3(const std::string& name, const glm::vec3& vec);

	void use();

private:
	GLint id;
};

extern Shader* loadShader(std::string vertexFile, std::string fragmentFile);
bool isSuccess(unsigned int shader, std::string type);
