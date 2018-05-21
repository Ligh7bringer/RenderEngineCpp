#include <cmath>
#include "entity.h"

Entity::Entity(const TexturedModel &_model, const glm::vec3 &_position, const glm::vec3 &_rotation, float _scale)
        : _model(_model), _position(_position), _rotation(_rotation), _scale(_scale), _textureIndex(0) {}

Entity::Entity(const TexturedModel &_model, int index, const glm::vec3 &_position, const glm::vec3 &_rotation,
               float _scale) : Entity(_model, _position, _rotation, _scale) {
    _textureIndex = index;
}

float Entity::getTextureXOffset() const {
    auto rowCount = _model.getTexture().getNumOfRows();
    auto column = _textureIndex % rowCount;
    return static_cast<float>(column) / static_cast<float>(rowCount);
}

float Entity::getTextureYOffset() const {
    auto rowCount = _model.getTexture().getNumOfRows();
    auto row = _textureIndex / rowCount;
    return static_cast<float>(row) / static_cast<float>(rowCount);
}

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

void Entity::setModel(const TexturedModel &model) {
    _model = model;
}

const glm::vec3 &Entity::getPosition() const {
    return _position;
}

void Entity::setPosition(const glm::vec3 &position) {
    _position = position;
}

const glm::vec3 &Entity::getRotation() const {
    return _rotation;
}

void Entity::setRotation(const glm::vec3 &rotation) {
    _rotation = rotation;
}

float Entity::getScale() const {
    return _scale;
}



