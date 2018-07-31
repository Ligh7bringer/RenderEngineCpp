#include <utilities/Log.h>
#include "particle_master.h"

ParticleMaster::ParticleMaster(const glm::mat4 &projMat) : _renderer(ParticleRenderer(projMat)) {


}

void ParticleMaster::update() {
    auto it = _particles.begin();

    while(it != _particles.end()) {
        auto stillAlive = it->update();
        if(!stillAlive)  {
            it = _particles.erase(it);
        } else {
            ++it;
        }
    }
}

void ParticleMaster::render(const Camera &camera) {
    _renderer.render(_particles, camera);
}

void ParticleMaster::addParticle(const glm::vec3 &position) {
    _particles.emplace_back(position, glm::vec3{0, 30.f, 0}, 1.f, 4.f, 0, 1.f);
}

