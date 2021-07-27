#pragma once
#include "Shader.h"
#include "ShaderType.h"
#include <array>

class ShaderCollection
{
public:
	static void Create();
	static Shader* GetShader(ShaderType shaderType);
private:
	void SetInitSettings();
	static ShaderCollection* instance;
	static std::array<Shader*, (int)ShaderType::SIZE> shaders;
	ShaderCollection();
	~ShaderCollection();
};
