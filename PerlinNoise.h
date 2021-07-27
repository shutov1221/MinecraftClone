#pragma once
#include <vector>

#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtc/type_ptr.hpp"

class PerlinNoise {
	std::vector<int> p;
public:
	PerlinNoise();
	PerlinNoise(unsigned int seed);
	double noise(double x, double y, double z);
	double noise(glm::vec3 vec);
private:
	double fade(double t);
	double lerp(double t, double a, double b);
	double grad(int hash, double x, double y, double z);
};
