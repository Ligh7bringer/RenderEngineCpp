#ifndef RENDERENGINE_PARTICLE_H
#define RENDERENGINE_PARTICLE_H

#include <glm/vec3.hpp>

class Particle {
public:
    Particle(const glm::vec3 &position, const glm::vec3 &velocity, float gravityEffect, float lifeLength,
             float rotation, float scale);

    bool update();

    const glm::vec3 &getPosition() const;
    float getRotation() const;
    float getScale() const;

private:
    float GRAVITY = -25.f;

    glm::vec3 _position;
    glm::vec3 _velocity;
    float _gravityEffect;
    float _lifeLength;
    float _rotation;
    float _scale;

    float _elapsedTime = 0;
};


#endif //RENDERENGINE_PARTICLE_H
