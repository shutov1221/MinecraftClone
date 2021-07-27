#pragma once
#include <unordered_map>
#include <vector>
#include "SuperChunk.h"
#include "ThreadPool.h"
#include "glm/gtx/hash.hpp"

using ChunkMap = std::unordered_map<glm::ivec2, Chunk_ptr>;

class ChunkManager
{
public:
	ChunkManager(SuperChunk* superchunk, Camera* camera);
	~ChunkManager();

	void UpdateChunksAroundPlayer();

	void AddChunk(int x, int z);
	void DeleteChunk(int x, int z);
	Chunk_ptr GetChunk(int x, int z);

private:
	bool AllNeighboursExist(glm::ivec2 pos);
	bool ChunkOutOfPlayerRange(int chunkX, int chunkZ);
	bool ChunkOutOfPlayerRange(glm::ivec2 pos);
	bool ChunkExistsAt(int x, int z);
	SuperChunk* superchunk;
	Camera* camera;
	ChunkMap chunks;

};