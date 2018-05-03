
#pragma once

#include <iostream>
#include <vector>
#include <string>
#include <fstream>

#include <array>

#include <GL/glew.h>
#include <GLFW/glfw3.h>

typedef std::array<float, 3> Color;

namespace Utility {
	GLuint loadShaders(
		std::string vertexFilePath, 
		std::string fragmentFilePath
	);
	
	GLFWwindow * initGLContext(
		GLFWkeyfun keyCB, 
		GLFWcursorposfun mousePosCB,
		GLFWmousebuttonfun mouseButtonCB,
		std::array<float, 2> screenSize
	);
};

