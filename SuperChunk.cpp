#include "SuperChunk.h"
#include <chrono>

SuperChunk::SuperChunk(Camera* camera, int threads) :
	Object(glm::vec3(0.0f)), camera(camera)
{
	perlin = new PerlinNoise(2454711);
	chunk_makers = new ThreadPool(threads);
	mesh_makers = new ThreadPool(threads);
}

SuperChunk::SuperChunk(glm::vec3 position, Camera* camera, int threads) :
	Object(position), camera(camera)
{
	perlin = new PerlinNoise(2411);
	chunk_makers = new ThreadPool(threads);
	mesh_makers = new ThreadPool(threads);
}

SuperChunk::~SuperChunk() {
	chunks.clear();
	delete perlin;
	delete chunk_makers;
	delete mesh_makers;
}

Chunk_ptr SuperChunk::AddChunk(int x, int z) {
	auto chunk = std::make_shared<Chunk>(glm::vec3(position.x + x, position.y, position.z + z), perlin);
	chunks.push_back(chunk);

	chunk_makers->enqueue([chunk] 
	{
		chunk->CreateChunk();
	});

	return chunk;
}


void SuperChunk::CalculateMesh(Chunk_ptr chunk) {
	if (camera->GetViewFrustum()->IsInFrustum(*chunk)) {
		chunk->ChangeMeshCalculatingStatus();
		mesh_makers->enqueue([chunk] 
		{
			chunk->BuildMesh();
		});
	}
}

void SuperChunk::DeleteChunk(Chunk_ptr chunk) {
	if (chunk == Chunk_ptr()) {
		return;
	}
	chunk->DeleteMesh();
	chunks.erase(std::remove(chunks.begin(), chunks.end(), chunk), chunks.end());
}

Chunk_ptr SuperChunk::GetChunk(int index) {
	if (index >= chunks.size() || index < 0) {
		return Chunk_ptr();
	}
	return chunks[index];
}

void SuperChunk::Draw(Renderer* renderer) {
	for (auto& chunk : chunks) {
		if (camera->GetViewFrustum()->IsInFrustum(*chunk)) {
			chunk->Draw(renderer);
		}
	}
}


