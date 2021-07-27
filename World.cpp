#include "World.h"

World* World::world = nullptr;
SuperChunk* World::superChunk = nullptr;
ChunkManager* World::chunkManager = nullptr;

World* World::CreateWorld(Camera* camera) {
	if (World::world == nullptr) {
		World::world = new World(camera);
	}

	return World::world;
}

World::World(Camera* camera) :
	camera(camera)
{
	superChunk = new SuperChunk(camera, 6);
	chunkManager = new ChunkManager(superChunk, camera);
}

World::~World() {;
	delete chunkManager;
	delete superChunk;
}

void World::Draw(Renderer* rendrer) {
	superChunk->Draw(rendrer);
}


void World::Update() {
	chunkManager->UpdateChunksAroundPlayer();
}

Block& World::GetBlock(const glm::vec3& position) {
	return GetBlock(position.x, position.y, position.z);
}

Block& World::GetBlock(const int& x, const int& y, const int& z) {

	if (y < 0 || y >= CHUNK_Y) {
		Block block;
		block.setBlockType(BlockType::Nothing);
		return block;
	}

	auto chunk = GetChunkByBlock(x, z);
	if (chunk == Chunk_ptr()) {
		Block block;
		block.setBlockType(BlockType::Nothing);
		return block;
	}

	const auto& chunkPos = chunk->GetPosition();
	
	int localX = x - (int)chunkPos.x;
	int localY = y;
	int localZ = z - (int)chunkPos.z;

	return chunk->GetBlock(localX, localY, localZ);
}

Chunk_ptr World::GetChunkByBlock(const int& x, const int& z) {

	int localX = (x < 0) ? -x : x;
	int localZ = (z < 0) ? -z : z;

	localX = (x < 0) ? ((x % CHUNK_X != 0) ? -(localX / CHUNK_X) - 1 : -(localX / CHUNK_X)) : localX / CHUNK_X;
	localZ = (z < 0) ? ((z % CHUNK_Z != 0) ? -(localZ / CHUNK_Z) - 1 : -(localZ / CHUNK_Z)) : localZ / CHUNK_Z;

	return chunkManager->GetChunk(localX * CHUNK_X, localZ * CHUNK_Z);
}

Chunk_ptr World::GetChunkByBlock(const glm::vec2& position) {
	return GetChunkByBlock(position.x, position.y);
}
