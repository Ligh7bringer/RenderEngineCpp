#include <engine/window_manager.h>
#include "camera.h"

#include <GLFW/glfw3.h>
#include <glm/detail/func_trigonometric.inl>

#include <cmath>
#include <Log.h>

Camera::Camera(const Player &pl) : _player(pl), _distanceFromPlayer(25.f), _pitch(0), _yaw(0), _angleAroundPlayer(0) {}

//handle keyboard input and change the camera's position accordingly
void Camera::move() {
    calculateZoom();
    calculatePitch();
    calculateAngleAroundPlayer();

    auto hDist = calculateHorizontalDistance();
    auto vDist = calculateVerticalDistance();
    calculatePosition(hDist, vDist);

    _yaw = 180.f - (_player.getRotation().y + _angleAroundPlayer);
}

void Camera::calculateZoom() {
    auto zoomLevel = WindowManager::getMouseWheel().y * 1.5f;
    _distanceFromPlayer -= zoomLevel;
    WindowManager::resetMouseWheel();
}

void Camera::calculatePitch() {
    if(glfwGetMouseButton(WindowManager::getWindow(), GLFW_MOUSE_BUTTON_RIGHT) == GLFW_PRESS) {
        auto pitchChange = WindowManager::getCursorDelta().y * 0.1f;
        _pitch -= pitchChange;
    }
}

void Camera::calculateAngleAroundPlayer() {
    if(glfwGetMouseButton(WindowManager::getWindow(), GLFW_MOUSE_BUTTON_LEFT) == GLFW_PRESS) {
        auto angleChange = WindowManager::getCursorDelta().x * 0.3f;
        _angleAroundPlayer -= angleChange;
    }
}

float Camera::calculateHorizontalDistance() {
    return _distanceFromPlayer * std::cos(glm::radians(_pitch));
}

float Camera::calculateVerticalDistance() {
    return _distanceFromPlayer * std::sin(glm::radians(_pitch));
}

void Camera::calculatePosition(float hdist, float vdist) {
    auto theta = _player.getRotation().y + _angleAroundPlayer;
    auto xOffset = hdist * std::sin(glm::radians(theta));
    auto zOffset = hdist * std::cos(glm::radians(theta));
    _position.x = _player.getPosition().x - xOffset;
    _position.z = _player.getPosition().z - zOffset;
    _position.y = _player.getPosition().y + vdist + 5.f;
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










