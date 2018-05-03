
#pragma once

#include <array>

#include <GLFW/glfw3.h>

#include <glm/glm.hpp>
#include <glm/ext.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/constants.hpp>

class Camera {
	public:
		Camera(GLFWwindow * window);
		
		void setPosition(glm::vec3 position);
		glm::vec3 getPosition();
		
		void rotate(float horizontal, float vertical);
		float getFOV();

		void handleInput();
				
		glm::mat4 getViewMatrix();
		glm::mat4 getPerspectiveMatrix();
		glm::mat4 getOrthographicMatrix();
		
	private:
		glm::mat4 viewMatrix;
		glm::mat4 projectionMatrix;
		
		glm::vec3 position;
		glm::vec3 up;
		glm::vec3 direction;
		
		float fov = 60;
		
		float nearPlaneDistance = 0.1f;
		float farPlaneDistance = 100;
		
		float horizontalAngle = 0; // radians
		float verticalAngle = 0; // in radians
		
		float speed = 10.0f;
		float mouseSpeed = 0.001f;
		float zoomSensitivity = -5.0f;
		
		std::array<float, 2> screenSize;
		
		GLFWwindow * window;
};
