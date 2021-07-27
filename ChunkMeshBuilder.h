#pragma once
#include "MeshBuilder.h"
#include "Chunk.h"

class ChunkMeshBuilder : public MeshBuilder<4>
{
public:
	ChunkMeshBuilder(Chunk* chunk);
	virtual ~ChunkMeshBuilder();

	virtual void BuildMesh() override;

private:
	void AddFace(Faces face, glm::vec3 position, BlockType blockType);
	void TryAddFace(int x, int y, int z, Faces face, BlockType blockType);
	bool ShouldAddFace(int x, int y, int z, Faces face);
	Chunk* chunk;

};

