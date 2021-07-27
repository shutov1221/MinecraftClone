//#include "Chunk.h"
#include "World.h"
#include "ChunkMeshBuilder.h"

Chunk::Chunk(glm::vec3 position, PerlinNoise* perlin) : 
    Object(position), Displayed<4>(new ChunkMeshBuilder(this)), perlin(perlin), blocks(nullptr)
{
}

Block& Chunk::GetBlock(int x, int y, int z) 
{
    if (OutOfBounds(x, y, z)) {
        glm::ivec3 pos = ToWorldPosition({ x, y, z });
        return World::GetBlock(pos.x, pos.y, pos.z);
    }

    if (!chunkReady)
    {
        std::unique_lock<std::mutex> lock(this->mtx);
        this->chunk_ready.wait(lock, [this]
            {
                return this->IsChunkReady();
            });
    }

    return blocks[GetBlockIndex(x, y, z)];
}

Chunk::~Chunk() {
    delete[] blocks;
}

void Chunk::CreateChunk() 
{
    float heightP = 0.0;
    int y_max = 0;

    blocks = new Block[CHUNK_VOLUME];

    for (int x = 0; x < CHUNK_X; x++) {
        for (int z = 0; z < CHUNK_Z; z++) {
            glm::vec3 worldPos = ToWorldPosition(glm::vec3(x, 1.0, z));

            y_max = perlin->noise(worldPos.x * 0.05f, worldPos.y * 0.01f, worldPos.z * 0.05f) * 0.9f * CHUNK_Y;

            for (int y = 0; y < y_max; y++) {

                auto blocktype = BlockType::AirBlock;

                if (y < y_max * 0.4) {
                    blocktype = BlockType::GrassBlock;
                }
                AddBlock(x, y, z, blocktype);
            }
        }
    }

    chunkReady = true;
    chunk_ready.notify_all();
}

void Chunk::AddBlock(int x, int y, int z, BlockType type) 
{
    if (OutOfBounds(x, y, z)) {
        return;
    }

    int index = GetBlockIndex(x, y, z);
    blocks[index].SetPosiiton(ToWorldPosition(x, y, z));
    blocks[index].setBlockType(type);
}

glm::ivec3 Chunk::ToWorldPosition(glm::vec3 position) 
{
    return this->position + position;
}

glm::ivec3 Chunk::ToWorldPosition(int x, int y, int z) const 
{
    return {
        position.x + x,
        position.y + y,
        position.z + z
    };
}

int Chunk::GetBlockIndex(int x, int y, int z) const 
{
    return x + CHUNK_X * (y + CHUNK_Y * z);
}

bool Chunk::OutOfBounds(int x, int y, int z) const 
{
	return x < 0
		|| x >= CHUNK_X
		|| y < 0
		|| y >= CHUNK_Y
		|| z < 0
		|| z >= CHUNK_Z;
}

bool Chunk::IsChunkReady() 
{
    return chunkReady;
}

void Chunk::ChangeMeshCalculatingStatus() 
{
    meshCalculatingNow = !meshCalculatingNow;
}

bool Chunk::GetMeshCalculatingStatus() 
{
    return meshCalculatingNow;
}