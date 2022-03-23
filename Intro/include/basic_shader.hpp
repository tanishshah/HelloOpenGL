#pragma once

#include<string>
#include<fstream>
#include<iostream>
#include<sstream>
#include<vector>

#include "GL/glew.h"
#include "glm/glm.hpp"

class basic_shader
{
public:
	basic_shader(std::string vertex_file, std::string fragment_file); // constructor
	~basic_shader(); // destructor

	void useProgram(); // use the shader
	bool is_good(); // ensure that shader class is working without errors

	// functions to support shader files
	void set_int(const std::string &var, int val) const;
	void set_float(const std::string &var, float val) const;
	void set_bool(const std::string &var, bool val) const;
	void set_vec2(const std::string& var, glm::vec2& val) const;
	void set_vec3(const std::string& var, glm::vec3& val) const;
	void set_vec4(const std::string& var, glm::vec4& val) const;

private:
	GLuint program;
};

