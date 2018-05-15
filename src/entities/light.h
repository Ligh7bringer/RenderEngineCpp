#ifndef RENDERENGINE_LIGHT_H
#define RENDERENGINE_LIGHT_H

#include <glm/vec3.hpp>

class Light {
public:
    explicit Light(const glm::vec3& pos, const glm::vec3& col) : _position(pos), _colour(col) {}

    const glm::vec3& getPosition() const { return _position; }
    const glm::vec3& getColour() const { return _colour; }
    void setPosition(const glm::vec3 pos) { _position = pos; }
    void setColour(const glm::vec3 col) {_colour = col; }

private:
    glm::vec3 _position;
    glm::vec3 _colour;
};


#endif //RENDERENGINE_LIGHT_H
