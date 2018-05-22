#ifndef RENDERENGINE_LIGHT_H
#define RENDERENGINE_LIGHT_H

#include <glm/vec3.hpp>

#include "../models/textured_model.h"

class Light {
public:
    Light(const glm::vec3& pos, const glm::vec3& col) :
            _position(pos), _colour(col) {}

    Light(const glm::vec3& pos, const glm::vec3& col, const glm::vec3& attenuation) :
            _position(pos), _colour(col), _attenuation(attenuation) {}

    const glm::vec3& getPosition() const { return _position; }
    const glm::vec3& getColour() const { return _colour; }
    const glm::vec3 &getAttenuation() const { return _attenuation; }

private:
    glm::vec3 _position;
    glm::vec3 _colour;
    glm::vec3 _attenuation{ 1.f, 0.f, 0.f };
};


#endif //RENDERENGINE_LIGHT_H
