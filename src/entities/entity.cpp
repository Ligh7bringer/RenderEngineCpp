#include "entity.h"

Entity::Entity(const TexturedModel &_model, const glm::vec3 &_position, const glm::vec3 &_rotation, float _scale)
        : _model(_model), _position(_position), _rotation(_rotation), _scale(_scale) {}

//scales the entity
void Entity::scale(float _scale) {
    Entity::_scale = _scale;
}

//moves the entity
void Entity::translate(float dx, float dy, float dz) {
    _position.x += dx;
    _position.y += dy;
    _position.z += dz;
}

//rotates the entity using Euler angles
void Entity::rotate(float dx, float dy, float dz) {
    _rotation.x += dx;
    _rotation.y += dy;
    _rotation.z += dz;
}

// -- getters and setters ----------------------------------
const TexturedModel &Entity::getModel() const {
    return _model;
}

void Entity::setModel(const TexturedModel &_model) {
    Entity::_model = _model;
}

const glm::vec3 &Entity::getPosition() const {
    return _position;
}

void Entity::setPosition(const glm::vec3 &_position) {
    Entity::_position = _position;
}

const glm::vec3 &Entity::getRotation() const {
    return _rotation;
}

void Entity::setRotation(const glm::vec3 &_rotation) {
    Entity::_rotation = _rotation;
}

float Entity::getScale() const {
    return _scale;
}

