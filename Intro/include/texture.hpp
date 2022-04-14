#pragma once

#include<string>
#include<iostream>

#include "GL/glew.h"
#include "glm/glm.hpp"


class Texture
{
public:
	bool is_good;
	GLuint texture;
	void use(); // use the texture
	Texture(const std::string& texture_file); // constructor for the texture class
	~Texture(); // destructor for the texture class
};

