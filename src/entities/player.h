#ifndef RENDERENGINE_PLAYER_H
#define RENDERENGINE_PLAYER_H

#include <terrains/terrain.h>
#include "entity.h"

class Player : public Entity {
public:
    Player(const TexturedModel &_model, const glm::vec3 &_position, const glm::vec3 &_rotation, float _scale);

    void getInput();
    void move(const Terrain &terrain);
    void jump();

private:
    float _currentSpeed;
    float _currentTurnSpeed;
    float _upwardsSpeed;
    bool _inAir;
};


#endif //RENDERENGINE_PLAYER_H
