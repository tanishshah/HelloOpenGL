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