#pragma once
#include "MeshBuilder.h"
#include "Rectangle.h"

class RectangleMeshBuilder : public MeshBuilder<4>
{
public:
	RectangleMeshBuilder(Rectangle* rectangle);
	virtual ~RectangleMeshBuilder();

	virtual void BuildMesh() override;

private:
	Rectangle* rectangle;
};

