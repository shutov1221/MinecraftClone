#pragma once
#include "BlockType.h"
#include "BlockProps.h"
#include <array>


class BlockBase
{
public: 
    static void Create();
    static BlockProps& GetBlockProps(BlockType type);
    ~BlockBase();
private:
    BlockBase();
    static std::array<BlockProps*, (int)BlockType::SIZE> blocks;
    static BlockBase* instance;

};

