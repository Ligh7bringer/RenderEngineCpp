#ifndef RENDERENGINE_PARTICLE_RENDERER_H
#define RENDERENGINE_PARTICLE_RENDERER_H

#include <glm/glm.hpp>

#include <vector>

#include <models/raw_model.h>
#include <shaders/shader.h>
#include <entities/camera.h>
#include "particle.h"

class ParticleRenderer {
public:
    explicit ParticleRenderer(const glm::mat4& projMat);
    ~ParticleRenderer() = default;

    void render(const std::vector<Particle>& particles, const Camera& camera);

private:
    std::vector<float> VERTICES = {-0.5f, 0.5f, -0.5f, -0.5f, 0.5f, 0.5f, 0.5f, -0.5f};

    RawModel _quad;
    Shader _shader;

    void prepare();
    void finishRendering();
    void updateModelViewMat(const glm::vec3& position, float rotation, float scale, const glm::mat4& viewMatrix);
};


#endif //RENDERENGINE_PARTICLE_RENDERER_H
