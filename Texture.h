#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <string>
#include "stb_image.h"

#include <iostream>

#pragma once
class Texture
{
public:
	unsigned int id;
	int width;
	int height;
	int nrChannels;

	Texture(unsigned int id, int width, int height, int nrChannels);
	~Texture();

	void bind();
};

extern Texture* load_texture(const char* filename);

