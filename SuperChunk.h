#pragma once
#include "Chunk.h"
#include "Renderer.h"
#include "ThreadPool.h"

class SuperChunk : public Object
{
public:
	SuperChunk(Camera* camera, int threads);
	SuperChunk(glm::vec3 position, Camera* camera, int threads);
	virtual ~SuperChunk();

	Chunk_ptr GetChunk(int index);

	void DeleteChunk(Chunk_ptr chunk);
	Chunk_ptr AddChunk(int x, int z);
	void Draw(Renderer* renderer);
	void CalculateMesh(Chunk_ptr chunk);

private:
	PerlinNoise* perlin;
	ThreadPool* chunk_makers;
	ThreadPool* mesh_makers;
	Camera* camera;
	std::vector<Chunk_ptr> chunks;

};

