#include "Block.h"

Block::Block() :
	type(BlockType::AirBlock), position(0.0f)
{
}

void Block::setBlockType(BlockType type) {
	this->type = type;
}

BlockType Block::getBlockType() {
	return type;
}

glm::vec3 Block::GetPosiion() {
	return position;
}
void Block::SetPosiiton(glm::vec3 position) {
	this->position = position;
}
