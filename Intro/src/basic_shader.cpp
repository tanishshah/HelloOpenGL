#include "basic_shader.hpp"

basic_shader::basic_shader(std::string vertex_file, std::string fragment_file){
	this->program = 0;
	std::stringstream str_stream, str_stream2;
	std::ifstream v_stream;
	std::ifstream f_stream;
	const GLchar* vertex_shader;
	const GLchar* fragment_shader;

	// read the shaders from their files
	try {
		v_stream.open(vertex_file);
		f_stream.open(fragment_file);

		if (v_stream.is_open() && f_stream.is_open()) {
			str_stream << v_stream.rdbuf();
			std::string v_s = (str_stream.str());
			str_stream2 << f_stream.rdbuf();
			std::string f_s = (str_stream2.str());
			vertex_shader = v_s.c_str();
			fragment_shader = f_s.c_str();
			f_stream.close();
			v_stream.close();

			// setup the vertex shader
			GLuint v_shader = glCreateShader(GL_VERTEX_SHADER);
			glShaderSource(v_shader, 1, &vertex_shader, nullptr);
			glCompileShader(v_shader);

			GLint status;
			GLchar log[512];

			glGetShaderiv(v_shader, GL_COMPILE_STATUS, &status);
			if (!status) {
				glGetShaderInfoLog(status, sizeof(log), nullptr, log);
				std::cerr << "Failed to compile vertex shader: " << log << std::endl;
			}

			// setup fragment shader
			GLint f_shader = glCreateShader(GL_FRAGMENT_SHADER);
			glShaderSource(f_shader, 1, &fragment_shader, nullptr);
			glCompileShader(f_shader);

			glGetShaderiv(f_shader, GL_COMPILE_STATUS, &status);
			if (!status) {
				glGetShaderInfoLog(f_shader, sizeof(log), nullptr, log);
				std::cerr << "Failed to compile fragment shader: " << log << std::endl;
			}

			// create program using shaders
			this->program = glCreateProgram();
			glAttachShader(this->program, v_shader);
			glAttachShader(this->program, f_shader);
			glLinkProgram(this->program);
			glDeleteShader(v_shader);
			glDeleteShader(f_shader);
			glGetProgramiv(this->program, GL_LINK_STATUS, &status);

			if (!status) {
				glGetProgramInfoLog(this->program, sizeof(log), nullptr, log);
				std::cerr << "Failed to link program: " << log << std::endl;
			}
		}
		else {
			std::cerr << "Failed to open a shader file" << std::endl;
		}
	}
	catch (std::exception e) {
		std::cerr << "Error reading a shader file" << std::endl;
	}
}

basic_shader::~basic_shader(){
	glDeleteProgram(this->program);
}


void basic_shader::useProgram(){
	glUseProgram(this->program);
}

bool basic_shader::is_good() {
	return !(this->program == 0);
}


