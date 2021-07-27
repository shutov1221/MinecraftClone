#include "ChunkMeshBuilder.h"
#include "BlockBase.h"

ChunkMeshBuilder::ChunkMeshBuilder(Chunk* chunk) :
	MeshBuilder<4>(new uint[4]{ 3, 2, 3, 0 }), chunk(chunk)
{
}

ChunkMeshBuilder::~ChunkMeshBuilder()
{
}

void ChunkMeshBuilder::BuildMesh() 
{
    if (hasMesh) {
        return;
    }

    for (int x = 0; x < CHUNK_X; x++) {
        for (int z = 0; z < CHUNK_Z; z++) {
            for (int y = 0; y < CHUNK_Y; y++) {
                Block block = chunk->GetBlock(x, y, z);
                BlockType blockType = block.getBlockType();
                if (blockType != BlockType::AirBlock && BlockBase::GetBlockProps(blockType).solid) {
                    TryAddFace(x, y, z, Faces::BackFace, blockType);
                    TryAddFace(x, y, z, Faces::LeftFace, blockType);
                    TryAddFace(x, y, z, Faces::RightFace, blockType);
                    TryAddFace(x, y, z, Faces::FrontFace, blockType);
                    TryAddFace(x, y, z, Faces::TopFace, blockType);
                    TryAddFace(x, y, z, Faces::BottomFace, blockType);
                }
            }
        }
    }

    hasMesh = true;
    chunk->ChangeMeshCalculatingStatus();
}

void ChunkMeshBuilder::AddFace(Faces face, glm::vec3 position, BlockType blockType) 
{
    float x = position.x;
    float y = position.y;
    float z = position.z;

    BlockProps prop = BlockBase::GetBlockProps(blockType);

    switch (face) {

    case(Faces::BackFace):
    {
        auto& t = prop.blockTex.back;

        std::array<Vertex, 4> back = {
           Vertex(glm::vec3(x + 0.5f, y - 0.5f,  z + 0.5f),  glm::vec2(t[1].x, t[1].y),     glm::vec3(0.0f, 0.0f, 1.0f)),
           Vertex(glm::vec3(x + 0.5f, y + 0.5f,  z + 0.5f),  glm::vec2(t[2].x, t[2].y),     glm::vec3(0.0f, 0.0f, 1.0f)),
           Vertex(glm::vec3(x - 0.5f, y + 0.5f,  z + 0.5f),  glm::vec2(t[3].x, t[3].y),     glm::vec3(0.0f, 0.0f, 1.0f)),
           Vertex(glm::vec3(x - 0.5f, y - 0.5f,  z + 0.5f),  glm::vec2(t[0].x, t[0].y),     glm::vec3(0.0f, 0.0f, 1.0f)),
        };

        vertices.push_back(back);

        indices.push_back(indicesCount);
        indices.push_back(indicesCount + 1);
        indices.push_back(indicesCount + 2);
        indices.push_back(indicesCount + 2);
        indices.push_back(indicesCount + 3);
        indices.push_back(indicesCount);

        indicesCount += 4;

        break;
    }

    case(Faces::FrontFace):
    {
        auto& t = prop.blockTex.front;

        std::array<Vertex, 4> front = {
           Vertex(glm::vec3(x + 0.5f, y + 0.5f, z - 0.5f),  glm::vec2(t[2].x, t[2].y),      glm::vec3(0.0f, 0.0f, -1.0f)),
           Vertex(glm::vec3(x + 0.5f, y - 0.5f, z - 0.5f),  glm::vec2(t[1].x, t[1].y),      glm::vec3(0.0f, 0.0f, -1.0f)),
           Vertex(glm::vec3(x - 0.5f, y - 0.5f, z - 0.5f),  glm::vec2(t[0].x, t[0].y),      glm::vec3(0.0f, 0.0f, -1.0f)),
           Vertex(glm::vec3(x - 0.5f, y + 0.5f, z - 0.5f),  glm::vec2(t[3].x, t[3].y),      glm::vec3(0.0f, 0.0f, -1.0f))
        };

        vertices.push_back(front);

        indices.push_back(indicesCount);
        indices.push_back(indicesCount + 1);
        indices.push_back(indicesCount + 2);
        indices.push_back(indicesCount + 2);
        indices.push_back(indicesCount + 3);
        indices.push_back(indicesCount);

        indicesCount += 4;

        break;
    }

    case(Faces::LeftFace):
    {
        auto& t = prop.blockTex.left;

        std::array<Vertex, 4> left = {
            Vertex(glm::vec3(x - 0.5f, y - 0.5f, z + 0.5f),  glm::vec2(t[1].x, t[1].y),      glm::vec3(-1.0f, 0.0f, 0.0f)),
            Vertex(glm::vec3(x - 0.5f, y + 0.5f, z + 0.5f),  glm::vec2(t[2].x, t[2].y),      glm::vec3(-1.0f, 0.0f, 0.0f)),
            Vertex(glm::vec3(x - 0.5f, y + 0.5f, z - 0.5f),  glm::vec2(t[3].x, t[3].y),      glm::vec3(-1.0f, 0.0f, 0.0f)),
            Vertex(glm::vec3(x - 0.5f, y - 0.5f, z - 0.5f),  glm::vec2(t[0].x, t[0].y),      glm::vec3(-1.0f, 0.0f, 0.0f))
        };

        vertices.push_back(left);

        indices.push_back(indicesCount);
        indices.push_back(indicesCount + 1);
        indices.push_back(indicesCount + 2);
        indices.push_back(indicesCount + 2);
        indices.push_back(indicesCount + 3);
        indices.push_back(indicesCount);

        indicesCount += 4;

        break;
    }

    case(Faces::RightFace):
    {
        auto& t = prop.blockTex.right;

        std::array<Vertex, 4> right = {
            Vertex(glm::vec3(x + 0.5f, y + 0.5f, z + 0.5f),  glm::vec2(t[3].x, t[3].y),      glm::vec3(1.0f, 0.0f, 0.0f)),
            Vertex(glm::vec3(x + 0.5f, y - 0.5f, z + 0.5f),  glm::vec2(t[0].x, t[0].y),      glm::vec3(1.0f, 0.0f, 0.0f)),
            Vertex(glm::vec3(x + 0.5f, y - 0.5f, z - 0.5f),  glm::vec2(t[1].x, t[1].y),      glm::vec3(1.0f, 0.0f, 0.0f)),
            Vertex(glm::vec3(x + 0.5f, y + 0.5f, z - 0.5f),  glm::vec2(t[2].x, t[2].y),      glm::vec3(1.0f, 0.0f, 0.0f))
        };

        vertices.push_back(right);

        indices.push_back(indicesCount);
        indices.push_back(indicesCount + 1);
        indices.push_back(indicesCount + 2);
        indices.push_back(indicesCount + 2);
        indices.push_back(indicesCount + 3);
        indices.push_back(indicesCount);

        indicesCount += 4;

        break;
    }

    case(Faces::BottomFace):
    {
        auto& t = prop.blockTex.bottom;

        std::array<Vertex, 4> bottom = {
            Vertex(glm::vec3(x + 0.5f, y - 0.5f, z - 0.5f),  glm::vec2(t[3].x, t[3].y),      glm::vec3(0.0f, -1.0f, 0.0f)),
            Vertex(glm::vec3(x + 0.5f, y - 0.5f, z + 0.5f),  glm::vec2(t[2].x, t[2].y),      glm::vec3(0.0f, -1.0f, 0.0f)),
            Vertex(glm::vec3(x - 0.5f, y - 0.5f, z + 0.5f),  glm::vec2(t[1].x, t[1].y),      glm::vec3(0.0f, -1.0f, 0.0f)),
            Vertex(glm::vec3(x - 0.5f, y - 0.5f, z - 0.5f),  glm::vec2(t[0].x, t[0].y),      glm::vec3(0.0f, -1.0f, 0.0f))
        };

        vertices.push_back(bottom);

        indices.push_back(indicesCount);
        indices.push_back(indicesCount + 1);
        indices.push_back(indicesCount + 2);
        indices.push_back(indicesCount + 2);
        indices.push_back(indicesCount + 3);
        indices.push_back(indicesCount);

        indicesCount += 4;

        break;
    }

    case(Faces::TopFace):
    {
        auto& t = prop.blockTex.top;

        std::array<Vertex, 4> top = {
           Vertex(glm::vec3(x + 0.5f, y + 0.5f,  z + 0.5f),  glm::vec2(t[2].x, t[2].y),     glm::vec3(0.0f, 1.0f, 0.0f)),
           Vertex(glm::vec3(x + 0.5f, y + 0.5f,  z - 0.5f),  glm::vec2(t[3].x, t[3].y),     glm::vec3(0.0f, 1.0f, 0.0f)),
           Vertex(glm::vec3(x - 0.5f, y + 0.5f,  z - 0.5f),  glm::vec2(t[0].x, t[0].y),     glm::vec3(0.0f, 1.0f, 0.0f)),
           Vertex(glm::vec3(x - 0.5f, y + 0.5f,  z + 0.5f),  glm::vec2(t[1].x, t[1].y),     glm::vec3(0.0f, 1.0f, 0.0f)),
        };

        vertices.push_back(top);

        indices.push_back(indicesCount);
        indices.push_back(indicesCount + 1);
        indices.push_back(indicesCount + 2);
        indices.push_back(indicesCount + 2);
        indices.push_back(indicesCount + 3);
        indices.push_back(indicesCount);

        indicesCount += 4;

        break;
    }

    default:
        std::cout << "Неверная поверхность!" << std::endl;
        break;
    }

}

void ChunkMeshBuilder::TryAddFace(int x, int y, int z, Faces face, BlockType blockType)
{
    if (ShouldAddFace(x, y, z, face)) {
        AddFace(face, chunk->ToWorldPosition({ x, y, z }), blockType);
    }
}

bool ChunkMeshBuilder::ShouldAddFace(int x, int y, int z, Faces face)
{
    bool result = false;

    switch (face) {

    case(Faces::RightFace):
    {
        if (chunk->GetBlock(x + 1, y, z).getBlockType() == BlockType::AirBlock)
            result = true;
        break;
    }
    case(Faces::BackFace):
    {
        if (chunk->GetBlock(x, y, z + 1).getBlockType() == BlockType::AirBlock)
            result = true;
        break;
    }
    case(Faces::LeftFace):
    {
        if (chunk->GetBlock(x - 1, y, z).getBlockType() == BlockType::AirBlock)
            result = true;
        break;
    }
    case(Faces::BottomFace):
    {
        if (chunk->GetBlock(x, y - 1, z).getBlockType() == BlockType::AirBlock)
            result = true;
        break;
    }
    case(Faces::TopFace):
    {
        if (chunk->GetBlock(x, y + 1, z).getBlockType() == BlockType::AirBlock)
            result = true;
        break;
    };
    case(Faces::FrontFace):
    {
        if (chunk->GetBlock(x, y, z - 1).getBlockType() == BlockType::AirBlock)
            result = true;
        break;
    }
    default:
        result = false;
        break;
    }

    return result;
}
