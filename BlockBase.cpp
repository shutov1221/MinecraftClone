#include "BlockBase.h"

BlockBase* BlockBase::instance = nullptr;
std::array<BlockProps*, (int)BlockType::SIZE> BlockBase::blocks = { nullptr };

BlockBase::BlockBase() {
    blocks[(int)BlockType::StoneBlock] = new BlockProps("stone");
    blocks[(int)BlockType::GrassBlock] = new BlockProps("grass");
    blocks[(int)BlockType::DirtBlock] = new BlockProps("dirt");
    blocks[(int)BlockType::WaterBlock] = new BlockProps("water");
}

BlockBase::~BlockBase() {
    for (auto& block : blocks) {
        delete block;
    }
}

void BlockBase::Create() {
    if (BlockBase::instance == nullptr) {
        BlockBase::instance = new BlockBase();
    }
}

BlockProps& BlockBase::GetBlockProps(BlockType type) {
    return *blocks[(int)type];
}