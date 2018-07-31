#include "particle.h"

#include <engine/window_manager.h>
#include <utilities/Log.h>

#define GLM_ENABLE_EXPERIMENTAL
#include <glm/gtx/string_cast.hpp>

Particle::Particle(const glm::vec3 &position, const glm::vec3 &velocity, float gravityEffect, float lifeLength,
                   float rotation, float scale) : _position(position), _velocity(velocity),
                                                    _gravityEffect(gravityEffect), _lifeLength(lifeLength),
                                                    _rotation(rotation), _scale(scale) {}

bool Particle::update() {
    auto dt = WindowManager::getDeltaTime();
    _velocity.y += GRAVITY * _gravityEffect * dt;
    auto change = _velocity;
    change *= dt;
    _position += change;
    _elapsedTime += dt;

    LOG(DEBUG) << "CHANGE: " << glm::to_string(change);
    LOG(DEBUG) << "POSITION: " << glm::to_string(_position);

    return _elapsedTime < _lifeLength;
}

//-------------
const glm::vec3 &Particle::getPosition() const {
    return _position;
}

float Particle::getRotation() const {
    return _rotation;
}

float Particle::getScale() const {
    return _scale;
}


