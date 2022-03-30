#pragma once

#include<string>
#include<iostream>

#include "GL/glew.h"
#include "glm/glm.hpp"

#ifndef STB_IMAGE_IMPLEMENTATION
#define STB_IMAGE_IMPLEMENTATION
#endif

#include "stb/stb_image.h"

class Texture
{
private:
	GLuint texture;
	bool is_good;

public:
	Texture(const std::string& texture_file); // constructor for the texture class
	~Texture(); // destructor for the texture class
};

