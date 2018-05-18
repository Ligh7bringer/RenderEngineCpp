#ifndef RENDERENGINE_CAMERA_H
#define RENDERENGINE_CAMERA_H

#include <glm/vec3.hpp>

#include "player.h"

class Camera {
public:
    explicit Camera(const Player &pl);

    const glm::vec3 &getPosition() const;
    float getPitch() const;
    float getYaw() const;
    float getRoll() const;

    void move();

private:
    glm::vec3 _position = glm::vec3(100.f, 2.f, -45.f);
    float _pitch;
    float _yaw;
    float _roll;

    float _distanceFromPlayer;
    float _angleAroundPlayer;

    const Player& _player;

    void calculateZoom();
    void calculatePitch();
    void calculateAngleAroundPlayer();
    float calculateHorizontalDistance();
    float calculateVerticalDistance();
    void calculatePosition(float hdist, float vdist);
};


#endif //RENDERENGINE_CAMERA_H
