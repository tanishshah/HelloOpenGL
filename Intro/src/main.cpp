#include<iostream>
#include<sstream>
#include "utils.hpp"

int main() {
	// set-up glfw, glew and create the window
	GLFWwindow* window = setup();
	if (!window) {
		glfwTerminate();
		return -1;
	}

	// allow the user to escape if the escape key is pressed
	glfwSetKeyCallback(window, exit_on_escape);

	// main window
	while (!glfwWindowShouldClose(window)) {
		glfwPollEvents();
		glClear(GL_COLOR_BUFFER_BIT);
		glfwSwapBuffers(window);
	}

	// exit out
	glfwTerminate();
	return 0;
}
