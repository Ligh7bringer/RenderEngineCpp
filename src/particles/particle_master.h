#ifndef RENDERENGINE_PARTICLE_MASTER_H
#define RENDERENGINE_PARTICLE_MASTER_H

#include <vector>

#include <glm/glm.hpp>

#include "particle.h"
#include "particle_renderer.h"

class ParticleMaster {
public:
    explicit ParticleMaster(const glm::mat4& projMat);
    ~ParticleMaster() = default;

    void update();
    void render(const Camera& camera);
    void addParticle(const glm::vec3 &position);

private:
    std::vector<Particle> _particles;
    ParticleRenderer _renderer;
};


#endif //RENDERENGINE_PARTICLE_MASTER_H
