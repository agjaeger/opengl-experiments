
#include <iostream>
#include <string>
#include <map>
#include <utility>

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>

#include "utility.hpp"
#include "camera.hpp"
#include "fsquad.hpp"

int main() {
	GLFWwindow * window = Utility::initGLContext(
		0, 
		0, 
		0,
		{480, 480}
	);
	
	GLuint programID = Utility::loadShaders(
		"src/shaders/rayMarcher.vert",
		"src/shaders/rayMarcher.frag"
	);
	
	Camera camera (window);
	
	FullScreenQuad fsq;
	fsq.initGL(programID);
	
	do {
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		//camera.handleInput();
		
		fsq.render(programID, camera.getViewMatrix(), camera.getOrthographicMatrix());
		
		// Swap buffers
		glfwSwapBuffers(window);
		glfwPollEvents();

	} while(
		glfwGetKey(window, GLFW_KEY_ESCAPE ) != GLFW_PRESS 
		&& glfwWindowShouldClose(window) == 0
	);
	
	return 0;
}
