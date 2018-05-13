#ifndef RENDERENGINE_ENTITY_H
#define RENDERENGINE_ENTITY_H


#include <models/textured_model.h>
#include <glm/vec3.hpp>

class Entity {
public:

private:
    TexturedModel _model;
    glm::vec3 _position;
    glm::vec3 _rotation;
    float _scale;
public:
    Entity(const TexturedModel &_model, const glm::vec3 &_position, const glm::vec3 &_rotation, float _scale);

    const TexturedModel &getModel() const;
    void setModel(const TexturedModel &_model);
    const glm::vec3 &getPosition() const;
    void setPosition(const glm::vec3 &_position);
    const glm::vec3 &getRotation() const;
    void setRotation(const glm::vec3 &_rotation);
    float getScale() const;
    void scale(float _scale);

    void translate(float dx, float dy, float dz);
    void rotate(float dx, float dy, float dz);
};


#endif //RENDERENGINE_ENTITY_H
