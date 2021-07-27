#pragma once
#include "Chunk.h"

class SubSuperChunk
{
public:
	SubSuperChunk(int size);
	void AddChunk(Chunk* chunk);
	void Draw(Renderer* renderer);
	void Clear();
private:

};

