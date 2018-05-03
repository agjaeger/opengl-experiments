
#include "utility.hpp"
#include <iostream>

void compileShader(GLuint shaderId, std::string filePath) {
	GLint result = GL_FALSE;
	int logLength;
	
	std::string shaderCode;
	std::ifstream shaderStream(filePath, std::ios::in);
	
	if (shaderStream.is_open()) {
		std::string line = "";
		while (getline(shaderStream, line))
			shaderCode += "\n" + line;
		shaderStream.close();
	}
	
	const char * shaderPointer = shaderCode.c_str();
	glShaderSource(shaderId, 1, &shaderPointer, NULL);
	glCompileShader(shaderId);
	
	glGetShaderiv(shaderId, GL_COMPILE_STATUS, &result);
	glGetShaderiv(shaderId, GL_INFO_LOG_LENGTH, &logLength);
	
	if (logLength > 0) {
		std::vector<char> shaderErrorMessage (logLength + 1);
		glGetShaderInfoLog(shaderId, logLength, NULL, &shaderErrorMessage[0]);
		std::cout << &shaderErrorMessage[0] << std::endl;
	}
}

GLuint Utility::loadShaders(std::string vertexFilePath, std::string fragmentFilePath) {
	GLuint vertexShaderId = glCreateShader(GL_VERTEX_SHADER);
	GLuint fragmentShaderId = glCreateShader(GL_FRAGMENT_SHADER);
	
	compileShader(vertexShaderId, vertexFilePath);
	compileShader(fragmentShaderId, fragmentFilePath);

	GLuint programId = glCreateProgram();
	glAttachShader(programId, vertexShaderId);
	glAttachShader(programId, fragmentShaderId);
	glLinkProgram(programId);
	
	GLint result = GL_FALSE;
	int logLength;
	
	glGetProgramiv(programId, GL_LINK_STATUS, &result);
	glGetProgramiv(programId, GL_INFO_LOG_LENGTH, &logLength);

	if (logLength > 0) {
		std::vector<char> programErrorMessage(logLength + 1);
		glGetProgramInfoLog(programId, logLength, NULL, &programErrorMessage[0]);
		std::cout << &programErrorMessage[0] << std::endl;
	}
	
	glDetachShader(programId, vertexShaderId);
	glDetachShader(programId, fragmentShaderId);
	
	glDeleteShader(vertexShaderId);
	glDeleteShader(fragmentShaderId);
	
	return programId;
}

GLFWwindow * Utility::initGLContext(
		GLFWkeyfun keyCB, 
		GLFWcursorposfun mousePosCB,
		GLFWmousebuttonfun mouseButtonCB,
		std::array<float, 2> screenSize) {
			
	GLFWwindow * window;

	if (!glfwInit()) {
		std::cout << "Error: Init Glfw" << std::endl;
	}
	
	glfwWindowHint(GLFW_SAMPLES, 4); // 4x antialiasing
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3); // We want OpenGL 3.3
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE); // To make MacOS happy; should not be needed
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE); //We don't want the old OpenGL 

	// Open a window and create its OpenGL context
	window = glfwCreateWindow(screenSize[0], screenSize[1], "floating", NULL, NULL);
	
	if( window == NULL ){
		std::cout << "Failed to open GLFW window." << std::endl;
		glfwTerminate();
	}
	
	glfwMakeContextCurrent(window); // Initialize GLEW
	
	glfwSetKeyCallback(window, keyCB);
	glfwSetCursorPosCallback(window, mousePosCB);
	glfwSetMouseButtonCallback(window, mouseButtonCB);
	
	glewExperimental=true; // Needed in core profile
	
	if (glewInit() != GLEW_OK) {
		std::cout << "Failed to initialize GLEW" << std::endl;
	}
	
	// Ensure we can capture the escape key being pressed below
	glfwSetInputMode(window, GLFW_STICKY_KEYS, GL_TRUE);
	glClearColor(0.9f, 0.9f, 0.9f, 1.0f);
	
	return window;
}
