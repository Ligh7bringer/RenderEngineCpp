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
    const glm::vec3 & getPlayerPosition() const;

    void move();

private:
    glm::vec3 _position;
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
