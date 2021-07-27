#pragma once
#include "Mesh.h"
#include "Texture.h"
#include "Shader.h"
#include "BlockType.h"

class Block
{
public:
	Block();

	void setBlockType(BlockType type);
	BlockType getBlockType();
	glm::vec3 GetPosiion();
	void SetPosiiton(glm::vec3 position);

private:
	BlockType type;
	glm::vec3 position;
};

