
#include "camera.hpp"

Camera::Camera(GLFWwindow * window) {
    this->window = window;
	
    int width, height;
    glfwGetFramebufferSize(window, &width, &height);
    screenSize = {(float) width, (float) height};
}

void Camera::setPosition(glm::vec3 position) {
    this->position = position;
}

glm::vec3 Camera::getPosition() {
    return position;
}

void Camera::rotate(float horizontal, float vertical) {
    horizontalAngle = horizontal;
    verticalAngle = vertical;
}

float Camera::getFOV() {
    return fov;
}

void Camera::handleInput() {
    static double lastTime = glfwGetTime();
    double currentTime = glfwGetTime();

    float deltaTime = float(currentTime - lastTime);

    double xPos = 0;
    double yPos = 0;

//  glfwGetCursorPos(window, &xPos, &yPos);
//	glfwSetCursorPos(window, 0, 0);

    horizontalAngle += mouseSpeed * float(-xPos);
    verticalAngle   += mouseSpeed * float(-yPos);

    direction = glm::vec3(
	glm::cos(verticalAngle) * glm::sin(horizontalAngle),
	glm::sin(verticalAngle),
	glm::cos(verticalAngle) * glm::cos(horizontalAngle)
    );

    glm::vec3 right = glm::vec3(
	glm::sin(horizontalAngle - glm::pi<float>()/2.0f),
	0,
	glm::cos(horizontalAngle - glm::pi<float>()/2.0f)
    );

    up = glm::cross(right, direction);

    if ((glfwGetKey(window, GLFW_KEY_W)) == GLFW_PRESS)
        position += direction * deltaTime * speed;
    if ((glfwGetKey(window, GLFW_KEY_S)) == GLFW_PRESS)
        position -= direction * deltaTime * speed;
    if ((glfwGetKey(window, GLFW_KEY_D)) == GLFW_PRESS)
        position += right * deltaTime * speed;
    if ((glfwGetKey(window, GLFW_KEY_A)) == GLFW_PRESS)
        position -= right * deltaTime * speed;

    float angle_delta = 0.05f;
    if ((glfwGetKey(window, GLFW_KEY_UP)) == GLFW_PRESS)
	    verticalAngle += angle_delta;
    if ((glfwGetKey(window, GLFW_KEY_DOWN)) == GLFW_PRESS)
	    verticalAngle -= angle_delta;
    if ((glfwGetKey(window, GLFW_KEY_LEFT)) == GLFW_PRESS)
	    horizontalAngle += angle_delta;
    if ((glfwGetKey(window, GLFW_KEY_RIGHT)) == GLFW_PRESS)
	    horizontalAngle -= angle_delta;

    lastTime = currentTime;
}

glm::mat4 Camera::getViewMatrix() {
    return glm::lookAt (
		position,           // Camera is here
		position+direction, // and looks here : at the same position, plus "direction"
		up
	);   
}

glm::mat4 Camera::getPerspectiveMatrix() {
    return glm::perspective(
		glm::radians(fov), 
		screenSize[0] / screenSize[1], 
		nearPlaneDistance, farPlaneDistance
    );
}

glm::mat4 Camera::getOrthographicMatrix() {
    return glm::ortho(
		0.0f, screenSize[0],
		screenSize[1], 0.0f,
		-0.1f, 10.0f
    );
}
