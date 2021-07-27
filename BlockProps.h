#pragma once
#include <string>
#include <fstream>
#include <iostream>
#include <sstream>
#include <array>

#include "glm/glm.hpp"

struct BlockTex {
    std::array<glm::vec2, 4> front;
    std::array<glm::vec2, 4> back;
    std::array<glm::vec2, 4> left;
    std::array<glm::vec2, 4> right;
    std::array<glm::vec2, 4> bottom;
    std::array<glm::vec2, 4> top;
};

class BlockProps
{
public:
	BlockProps(const std::string block);
    BlockTex blockTex;
    bool solid;
};

