#pragma once
#include <memory>
#include "Vertex.h"

class Chunk;

template<int T>
using Vertices = std::vector<std::array<Vertex, T>>;

using BlockVertices = Vertices<32>;
using SphereVertices = Vertices<6>;
using BoundingBoxVertices = SphereVertices;
using ScreenVertices = Vertices<20>;
using LightBlockVertices = Vertices<18>;

using Chunk_ptr = std::shared_ptr<Chunk>;

using uint = unsigned int;
