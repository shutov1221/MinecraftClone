#pragma once
#include <stdint.h>

enum class BlockType : uint8_t
{
	Nothing = 0,
	AirBlock = 1,
	WaterBlock,
	GrassBlock,
	StoneBlock,
	DirtBlock,

	SIZE
};

