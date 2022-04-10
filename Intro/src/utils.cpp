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

	// define vertices
	GLfloat vertices[] = {
		0.0f, 0.5f, 0.0f, 0.5f, 1.0f,
		0.5f, -0.5f, 0.0f, 1.0f, 0.0f
		-0.5f, -0.5f, 0.0f, 0.0f, 0.0f
	};

	GLuint vbo, vao; // gl vertex buffer object and vertex array object

	// setup buffer onject
	glGenBuffers(1, &vbo);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	// setup array object
	glGenVertexArrays(1, &vao);
	glBindVertexArray(vao);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(GLfloat), nullptr);
	glEnableVertexAttribArray(0);

	//texture co-ordinates
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(GLfloat), (void*)(3 * sizeof(GLfloat)));
	glEnableVertexAttribArray(1);

	std::vector<GLuint> v;
	v.push_back(vbo);
	v.push_back(vao);

	// get the shaders from the basic_shader class
	return v;
}

// Draw a quad
std::vector<GLuint> quad() {

	// define vertices
	GLfloat vertices[] = {
		 0.5f,  0.5f, 0.0f,
		 0.5f, -0.5f, 0.0f,
		-0.5f, -0.5f, 0.0f,
		-0.5f,  0.5f, 0.0f
	};

	unsigned int indices[] = {
		0, 1, 3,
		1, 2, 3
	};

	GLuint vbo, vao, ebo; // gl vertex buffer object and vertex array object

	glGenVertexArrays(1, &vao);
	glGenBuffers(1, &vbo);
	glGenBuffers(1, &ebo);
	glBindVertexArray(vao);

	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), nullptr);
	glEnableVertexAttribArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);

	std::vector<GLuint> v;
	v.push_back(vbo);
	v.push_back(vao);
	v.push_back(ebo);

	// get the shaders from the basic_shader class
	return v;
}