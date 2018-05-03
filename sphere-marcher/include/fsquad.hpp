
#pragma once

#include <array>
#include <GL/glew.h>
#include <glm/glm.hpp>
#include "utility.hpp"

class FullScreenQuad {
	public:
		FullScreenQuad ();
		
		void initGL (
			GLuint programID
		);
		
		void render (
			GLuint programID,
			glm::mat4 viewMatrix, 
			glm::mat4 projectionMatrix
		);
		
	private:	
		struct Buffers {
			GLuint vertex;
		};
		
		struct Handles {
			GLuint pvm;
		};
	
		Buffers buffers;
		Handles handles;
		
		glm::mat4 modelMatrix = glm::mat4();		

		GLuint vao;
};
