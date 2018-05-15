#ifndef RENDERENGINE_CAMERA_H
#define RENDERENGINE_CAMERA_H

#include <glm/vec3.hpp>

class Camera {
public:
    Camera() = default;

    const glm::vec3 &getPosition() const;
    float getPitch() const;
    float getYaw() const;
    float getRoll() const;

    void move();

private:
    glm::vec3 _position = glm::vec3(0.f, 2.f, 0.f);
    float _pitch;
    float _yaw;
    float _roll;
};


#endif //RENDERENGINE_CAMERA_H
