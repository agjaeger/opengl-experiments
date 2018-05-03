
#include "fsquad.hpp"

static const GLfloat vertex_buffer_data[] = {
    -1.0f, -1.0f, 0.0f,
    1.0f, -1.0f, 0.0f,
    -1.0f,  1.0f, 0.0f,
    
    -1.0f,  1.0f, 0.0f,
    1.0f, -1.0f, 0.0f,
    1.0f,  1.0f, 0.0f
};

FullScreenQuad::FullScreenQuad () {}

void
FullScreenQuad::initGL (
	GLuint programID
) {
	glGenVertexArrays(1, &vao);
	glBindVertexArray(vao);
	
	glGenBuffers(1, &buffers.vertex);
	glBindBuffer(GL_ARRAY_BUFFER, buffers.vertex);
	
	glBufferData(
		GL_ARRAY_BUFFER, 
		sizeof(vertex_buffer_data), 
		vertex_buffer_data, GL_STATIC_DRAW
	);

	handles.pvm = glGetUniformLocation(programID, "pvm");
}

void 
FullScreenQuad::render (
	GLuint programID,
	glm::mat4 viewMatrix,
	glm::mat4 projectionMatrix
) {
	glUseProgram(programID);
	
	glEnableVertexAttribArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, buffers.vertex);
		
	glm::mat4 pvm = glm::mat4(); //projectionMatrix * viewMatrix * modelMatrix;
	
	glUniformMatrix4fv(handles.pvm, 1, GL_FALSE, &pvm[0][0]);
	
	glVertexAttribPointer(
		0,			// first index
		3,			// length
		GL_FLOAT,	// type
		GL_FALSE,	// normalized
		0,			// stride
		(void *) 0	// data
	);
	
	glDrawArrays(GL_TRIANGLES, 0, 6);
	
	glDisableVertexAttribArray(0);
	glUseProgram(0);
}
