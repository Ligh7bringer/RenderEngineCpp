#include <GLFW/glfw3.h>
#include <engine/window_manager.h>
#include "camera.h"

//the movement speed of the camera
const float SPEED = 0.3f;

//handle keyboard input and change the camera's position accordingly
void Camera::move() {
//    if(glfwGetKey(WindowManager::getWindow(), GLFW_KEY_W) == GLFW_PRESS) {
//        _position.z -= SPEED;
//    }
//    if(glfwGetKey(WindowManager::getWindow(), GLFW_KEY_D) == GLFW_PRESS) {
//        _position.x += SPEED;
//    }
//    if(glfwGetKey(WindowManager::getWindow(), GLFW_KEY_A) == GLFW_PRESS) {
//        _position.x -= SPEED;
//    }
//    if(glfwGetKey(WindowManager::getWindow(), GLFW_KEY_S) == GLFW_PRESS) {
//        _position.z += SPEED;
//    }
//    if(glfwGetKey(WindowManager::getWindow(), GLFW_KEY_SPACE) == GLFW_PRESS) {
//        _position.y += SPEED;
//    }
//    if(glfwGetKey(WindowManager::getWindow(), GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS) {
//        _position.y -= SPEED;
//    }
}

// -- getters --------------------------------
const glm::vec3 &Camera::getPosition() const {
    return _position;
}

float Camera::getPitch() const {
    return _pitch;
}

float Camera::getYaw() const {
    return _yaw;
}

float Camera::getRoll() const {
    return _roll;
}
