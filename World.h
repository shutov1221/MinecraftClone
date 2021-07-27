#pragma once
#include "ChunkManager.h"
#include "SuperChunk.h"
#include "BlockBase.h"

class World
{
public:
	static World* CreateWorld(Camera* camera);

	static Block& GetBlock(const int& x, const int& y, const int& z);
	static Block& GetBlock(const glm::vec3& position);

	static Chunk_ptr GetChunkByBlock(const int& x, const int& z);
	static Chunk_ptr GetChunkByBlock(const glm::vec2& position);

	static void Draw(Renderer* rendrer);
	static void Update();

	~World();
private:	
	static World* world;
	static SuperChunk* superChunk;
	static ChunkManager* chunkManager;
	World(Camera* camera);
	Camera* camera;
};


