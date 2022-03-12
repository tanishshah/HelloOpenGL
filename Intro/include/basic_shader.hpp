#pragma once

#include<string>
#include<fstream>
#include<iostream>
#include<sstream>

#include "GL/glew.h"

class basic_shader
{
public:
	basic_shader(std::string vertex_file, std::string fragment_file);
	~basic_shader();

	void useProgram();
	bool is_good();

private:
	GLuint program;
};

