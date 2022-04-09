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
	std::vector<GLuint> v = first_triangle();
	// shader for the triangle
	basic_shader* triangle_shader = new basic_shader(".\\resources\\triangle_vs.txt", ".\\resources\\triangle_fs.txt");
	//texture 
	Texture* triangle_texture = new Texture(".\\resources\\star.png");

	// main window
	bool exit = false;
	while (!glfwWindowShouldClose(window) && !exit) {
		glfwPollEvents();
		glClear(GL_COLOR_BUFFER_BIT);
		if (triangle_shader->is_good()) {
			triangle_shader->useProgram();
			//auto colour = glm::vec4(0.3f, 0.2f, 0.1f, 1.0f);
			//triangle_shader->set_vec4("triangle_colour", colour);
		}
		else {
			std::cerr << "Shader program failed" << std::endl;
			exit = true;
		}
		triangle_texture->use();
		glBindVertexArray(v[1]);
		glDrawArrays(GL_TRIANGLES, 0, 3);
		glBindVertexArray(0);

		glfwSwapBuffers(window);
	}

	// exit out
	triangle_shader = nullptr;
	delete triangle_shader;
	glDeleteVertexArrays(1, &v[1]);
	glDeleteBuffers(1, &v[0]);
	glfwTerminate();
	return 0;
}
