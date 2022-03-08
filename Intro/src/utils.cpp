#include "utils.hpp"

const int WINDOW_WIDTH = 800;
const int WINDOW_HEIGHT = 800;
const char* WINDOW_TITLE = "Window";

// setup glfw, glew, and create the window
GLFWwindow* setup() {
	// set-up glfw
	if (!glfwInit()) {
		std::cerr << "Failed to initialize GLFW";
		return nullptr;
	}

	// give glfw hints
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	// create the window
	GLFWwindow* window = glfwCreateWindow(WINDOW_WIDTH, WINDOW_HEIGHT, WINDOW_TITLE, NULL, NULL);

	if (!window) {
		std::cerr << "Failed to create window";
		glfwTerminate();
		return nullptr;
	}

	glfwMakeContextCurrent(window);

	// set-up glew
	if (glewInit() != GLEW_OK) {
		std::cerr << "Failed to initialize glew";
		return nullptr;
	}

	return window;
}

// close the window if the escape key is pressed
void exit_on_escape(GLFWwindow* window, int key, int scancode, int action, int mode) {
	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS) {
		glfwSetWindowShouldClose(window, GL_TRUE);
	}
}

// Draw a triangle
std::vector<GLuint> first_triangle() {
	// shaders
	// vertex shader 
	const GLchar* vertex_shader =
		"#version 330\n"
		"layout (location = 0) in vec3 loc;"
		"void main()"
		"{"
		"	gl_Position = vec4(loc.x, loc.y, loc.z, 1.0);"
		"}";

	// fragment shader
	const GLchar* fragment_shader =
		"#version 330\n"
		"out vec4 colour;"
		"void main()"
		"{"
		"	colour = vec4(0.4f, 0.1f, 0.4f, 1.0f);"
		"}"
		"";

	// define vertices
	GLfloat vertices[] = {
		0.0f, 0.1f, 0.0f,
		0.1f, -0.1f, 0.0f,
		-0.1f, -0.1f, 0.0f
	};

	GLuint vbo, vao; // gl vertex buffer object and vertex array object

	// setup buffer onject
	glGenBuffers(1, &vbo);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	// setup array object
	glGenVertexArrays(1, &vao);
	glBindVertexArray(vao);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, nullptr);
	glEnableVertexAttribArray(0);

	// setup vertex shader
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
	GLuint program = glCreateProgram();
	glAttachShader(program, v_shader);
	glAttachShader(program, f_shader);
	glLinkProgram(program);
	glDeleteShader(v_shader);
	glDeleteShader(f_shader);
	glGetProgramiv(program, GL_LINK_STATUS, &status);

	if (!status) {
		glGetProgramInfoLog(program, sizeof(log), nullptr, log);
		std::cerr << "Failed to link program: " << log << std::endl;
	}

	std::vector<GLuint> v;
	v.push_back(vbo);
	v.push_back(vao);
	v.push_back(program);

	return v;
}