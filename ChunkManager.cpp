#include "ChunkManager.h"

ChunkManager::ChunkManager(SuperChunk* superchunk, Camera* camera) :
	superchunk(superchunk), camera(camera)
{
}

ChunkManager::~ChunkManager() {
	chunks.clear();
}

void ChunkManager::UpdateChunksAroundPlayer() {
	glm::vec3 cameraPosition = camera->GetPosition();

	int x = static_cast<int>(cameraPosition.x / CHUNK_X);
	int z = static_cast<int>(cameraPosition.z / CHUNK_Z);

	std::erase_if(chunks, [&](const auto& chunk) 
	{
		auto const& [key, value] = chunk;
		if (ChunkOutOfPlayerRange(key)) {
			superchunk->DeleteChunk(GetChunk(key.x, key.y));
			return true;
		}
		return false;
	});

	for (int i = x - CHUNKS_AROUND; i < x + CHUNKS_AROUND; i++) {
		for (int j = z - CHUNKS_AROUND; j < z + CHUNKS_AROUND; j++) {
			AddChunk(i * CHUNK_X, j * CHUNK_Z);
		}
	}

	for (auto& chunk : chunks) {
		if (AllNeighboursExist(chunk.first) 
			&& !chunk.second->IsMeshReady()
			&& !chunk.second->GetMeshCalculatingStatus()) 
		{
			superchunk->CalculateMesh(chunk.second);
		}
	}
}

void ChunkManager::AddChunk(int x, int z) {
	if (!ChunkExistsAt(x, z)) {
		glm::ivec2 key = { x, z };
		chunks.emplace(key, superchunk->AddChunk(x, z));
	}
}

bool ChunkManager::AllNeighboursExist(glm::ivec2 pos) {
	if (GetChunk(pos.x + CHUNK_X, pos.y) == Chunk_ptr()) {
		return false;
	}
	if (GetChunk(pos.x - CHUNK_X, pos.y) == Chunk_ptr()) {
		return false;
	}
	if (GetChunk(pos.x, pos.y + CHUNK_Z) == Chunk_ptr()) {
		return false;
	}
	if (GetChunk(pos.x, pos.y - CHUNK_Z) == Chunk_ptr()) {
		return false;
	}	

	return true;
}

void ChunkManager::DeleteChunk(int x, int z) {
	glm::ivec2 key = { x, z };
	if (ChunkExistsAt(key.x, key.y)) {
		if (chunks[key]->IsMeshReady() && chunks[key]->IsChunkReady()) {
			superchunk->DeleteChunk(GetChunk(x, z));
			chunks.erase(key);
		}
	}
}


bool ChunkManager::ChunkExistsAt(int x, int z) {
	glm::ivec2 key = { x, z };
	bool result = false;
	try {
		result = chunks.find(key) != chunks.end();
		return result;
	}
	catch (glm::ivec2) {
		std::cout << "ChunkExistAt() Error at position x = " << key.x << " y = " << key.y << std::endl;
		return result;
	}

}

bool ChunkManager::ChunkOutOfPlayerRange(int chunkX, int chunkZ) {
	const auto& cameraPosition = camera->GetPosition();

	int x = static_cast<int>(cameraPosition.x / CHUNK_X);
	int z = static_cast<int>(cameraPosition.z / CHUNK_Z);

	if (chunkX > (x + CHUNKS_AROUND) * CHUNK_X ||
		chunkX < (x - CHUNKS_AROUND) * CHUNK_X ||
		chunkZ > (z + CHUNKS_AROUND) * CHUNK_Z ||
		chunkZ < (z - CHUNKS_AROUND) * CHUNK_Z)
	{
		return true;
	}

	return false;
}

bool ChunkManager::ChunkOutOfPlayerRange(glm::ivec2 pos) {
	const auto& cameraPosition = camera->GetPosition();

	int x = static_cast<int>(cameraPosition.x / CHUNK_X);
	int z = static_cast<int>(cameraPosition.z / CHUNK_Z);

	if (pos.x > (x + CHUNKS_AROUND) * CHUNK_X ||
		pos.x < (x - CHUNKS_AROUND) * CHUNK_X ||
		pos.y > (z + CHUNKS_AROUND) * CHUNK_Z ||
		pos.y < (z - CHUNKS_AROUND) * CHUNK_Z)
	{
		return true;
	}

	return false;
}

Chunk_ptr ChunkManager::GetChunk(int x, int z) {
	if (!ChunkExistsAt(x, z)) {
		return Chunk_ptr();
	}
	glm::ivec2 key = { x, z };
	return chunks[key];
}
