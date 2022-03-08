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

	// render a triangle
	std::vector<GLuint> v = first_triangle();

	// main window
	while (!glfwWindowShouldClose(window)) {
		glfwPollEvents();
		glClear(GL_COLOR_BUFFER_BIT);
		glUseProgram(v[2]);
		glBindVertexArray(v[1]);
		glDrawArrays(GL_TRIANGLES, 0, 3);
		glBindVertexArray(0);

		glfwSwapBuffers(window);
	}

	// exit out
	glDeleteProgram(v[2]);
	glDeleteVertexArrays(1, &v[1]);
	glDeleteBuffers(1, &v[0]);
	glfwTerminate();
	return 0;
}
