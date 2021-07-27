#pragma once
#include "IDraw.h"
#include "MeshBuilder.h"

template<int T>
class Displayed : public IDraw
{
public:

	Displayed(MeshBuilder<T>* meshBuilder) :
		meshBuilder(meshBuilder)
	{
	}

	virtual ~Displayed()
	{
		delete meshBuilder;
	}

	virtual void Draw(Renderer* renderer) override
	{
		if (meshBuilder->IsMeshReady()) {
			meshBuilder->BindMesh();
			renderer->Render(meshBuilder->GetMesh(), GL_TRIANGLES);
		}
	}

	void BuildMesh()
	{
		meshBuilder->BuildMesh();
	}

	void DeleteMesh()
	{
		meshBuilder->DeleteMesh();
	}

	bool IsMeshReady()
	{
		return meshBuilder->IsMeshReady();
	}

	Mesh<T>* GetMesh()
	{
		return meshBuilder->GetMesh();
	}

private:
	MeshBuilder<T>* meshBuilder;
};

