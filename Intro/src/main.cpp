#include "utils.hpp"
#include "basic_shader.hpp"
#include "texture.hpp"
int main() {
	// set-up glfw, glew and create the window
	GLFWwindow* window = setup();
	if (!window) {
		glfwTerminate();
		return -1;
	}

	// allow the user to escape if the escape key is pressed
	glfwSetKeyCallback(window, exit_on_escape);

	// make a triangle
	std::vector<GLuint> v = quad();

	// shader
	basic_shader* shader = new basic_shader(".\\resources\\triangle_vs.txt", ".\\resources\\triangle_fs.txt");

	//texture 
	//Texture* triangle_texture = new Texture(".\\resources\\star.png");

	// main window
	bool exit = false;
	while (!glfwWindowShouldClose(window) && !exit) {
		glfwPollEvents();
		glClear(GL_COLOR_BUFFER_BIT);
		if (shader->is_good()) {
			shader->useProgram();
			auto colour = glm::vec4(0.3f, 0.2f, 0.1f, 1.0f);
			shader->set_vec4("triangle_colour", colour);
		}
		else {
			std::cerr << "Shader program failed" << std::endl;
			exit = true;
		}

		glBindVertexArray(v[1]);
		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

		glfwSwapBuffers(window);
	}

	// exit out
	shader = nullptr;
	delete shader;
	glDeleteVertexArrays(1, &v[1]);
	glDeleteBuffers(1, &v[0]);
	glDeleteBuffers(1, &v[2]);

	glfwTerminate();
	return 0;
}
