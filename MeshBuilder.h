#pragma once
#include <vector>
#include <array>
#include <atomic>
#include "Mesh.h"

template<int T>
class MeshBuilder
{
public:
	MeshBuilder(uint* attributes) :
		mesh(new Mesh<T>(attributes))
	{

	}
	virtual ~MeshBuilder()
	{

	}
	
	virtual void BuildMesh() = 0;
	
	virtual void BindMesh()
	{
		if (!alreadyBinded) {
			if (!indices.empty() && !vertices.empty()) {
				mesh->BindVertexArray(vertices, indices);
				alreadyBinded = true;
			}
		}
	}

	virtual void UnBindMesh()
	{
		alreadyBinded = false;
	}

	virtual void DeleteMesh()
	{
		if (mesh != nullptr) {
			delete mesh;
			mesh == nullptr;
		}
	}

	bool IsMeshReady()
	{
		return hasMesh;
	}

	Mesh<T>* GetMesh()
	{
		return mesh;
	}

protected:
	std::vector<std::array<Vertex, T>> vertices;
	std::vector<int> indices;
	Mesh<T>* mesh;

	std::atomic<bool> hasMesh{ false };
	bool alreadyBinded = false;
	int indicesCount = 0;
};

