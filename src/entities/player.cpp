#include "player.h"
#include <engine/window_manager.h>
#include <Log.h>

#include <GLFW/glfw3.h>

#include <cmath>

const float RUN_SPEED = 10.f;
const float TURN_SPEED = 100.f;
const float GRAVITY = -25.f;
const float JUMP_POWER = 12.f;
const float TERRAIN_HEIGHT = 0.f;

Player::Player(const TexturedModel &_model, const glm::vec3 &_position, const glm::vec3 &_rotation, float _scale)
        : Entity(_model, _position, _rotation, _scale), _currentTurnSpeed(0), _currentSpeed(0), _upwardsSpeed(0), _inAir(false) {}

void Player::move() {
    getInput();

    auto dt = WindowManager::getDeltaTime();
    rotate(0.f, _currentTurnSpeed * dt, 0.f);
    auto distance = _currentSpeed * dt;
    auto dx = distance * std::sin(toRadians(getRotation().y));
    auto dz = distance * std::cos(toRadians(getRotation().y));
    translate(dx, 0, dz);

    _upwardsSpeed += GRAVITY * dt;
    translate(0.f, _upwardsSpeed * dt, 0.f);
    if(getPosition().y < TERRAIN_HEIGHT) {
        _upwardsSpeed = 0;
        _position.y = TERRAIN_HEIGHT;
        _inAir = false;
    }
}

void Player::getInput() {
    if(glfwGetKey(WindowManager::getWindow(), GLFW_KEY_W) == GLFW_PRESS) {
        _currentSpeed = RUN_SPEED;
    } else if(glfwGetKey(WindowManager::getWindow(), GLFW_KEY_S) == GLFW_PRESS) {
        _currentSpeed = -RUN_SPEED;
    } else {
        _currentSpeed = 0;
    }

    if(glfwGetKey(WindowManager::getWindow(), GLFW_KEY_D) == GLFW_PRESS) {
        _currentTurnSpeed = -TURN_SPEED;
    } else  if(glfwGetKey(WindowManager::getWindow(), GLFW_KEY_A) == GLFW_PRESS) {
        _currentTurnSpeed = TURN_SPEED;
    } else {
        _currentTurnSpeed = 0;
    }


    if(glfwGetKey(WindowManager::getWindow(), GLFW_KEY_SPACE) == GLFW_PRESS) {
        jump();
    }
}

void Player::jump() {
    if(!_inAir) {
        _upwardsSpeed = JUMP_POWER;
        _inAir = true;
    }
}

float Player::toRadians(float deg) {
    return static_cast<float>(deg * M_PI / 180.0);
}


