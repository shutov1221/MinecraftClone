#pragma once
#include "Block.h"
#include "WorldConstants.h"
#include "Faces.h"
#include <vector>
#include <array>
#include "PerlinNoise.h"
#include <condition_variable>
#include <mutex>
#include <atomic>
#include <chrono>
#include "Renderer.h"
#include "Object.h"
#include "Displayed.h"

class ChunkMeshBuilder;

class Chunk : public Object, public Displayed<4>
{
public:
	Chunk(glm::vec3 position, PerlinNoise* perlin);
	virtual ~Chunk();

	void AddBlock(int x, int y, int z, BlockType type);

	void CreateChunk();

	bool IsChunkReady();
	void ChangeMeshCalculatingStatus();
	bool GetMeshCalculatingStatus();

	Block& GetBlock(int x, int y, int z);

private:
	bool chunkReady = false;
	std::atomic<bool> meshCalculatingNow{ false };

	Block* blocks;

	PerlinNoise* perlin;

	std::mutex mtx;
	std::condition_variable chunk_ready;

	glm::ivec3 ToWorldPosition(glm::vec3 position);
	glm::ivec3 ToWorldPosition(int x, int y, int z) const;
	int GetBlockIndex(int x, int y, int z) const;
	bool OutOfBounds(int x, int y, int z) const;

	friend class ChunkMeshBuilder;
};

