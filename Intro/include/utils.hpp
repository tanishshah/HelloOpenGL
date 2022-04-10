#pragma once

#include<iostream>
#include<vector>

#ifndef GLEW_STATIC
#define GLEW_STATIC
#endif

#include "GL/glew.h"
#include "GLFW/glfw3.h"

// Function to handle setting up glew and create the glfw window
GLFWwindow* setup();

// Function for using the escape key to get out of the window
void exit_on_escape(GLFWwindow* window, int key, int scancode, int action, int mode);
std::vector<GLuint> first_triangle();
std::vector<GLuint> quad();