#ifndef RENDERENGINE_PLAYER_H
#define RENDERENGINE_PLAYER_H

#include "entity.h"

class Player : public Entity {
public:
    Player(const TexturedModel &_model, const glm::vec3 &_position, const glm::vec3 &_rotation, float _scale);

    void getInput();
    void move();
    void jump();

private:
    float _currentSpeed;
    float _currentTurnSpeed;
    float _upwardsSpeed;
    bool _inAir;

    float toRadians(float deg);
};


#endif //RENDERENGINE_PLAYER_H
