#include "particle_renderer.h"

#include <engine/loader.h>
#include <utilities/maths.h>

#include <glm/gtc/matrix_transform.hpp>
#include <utilities/gl_error.h>
#include <utilities/Log.h>

ParticleRenderer::ParticleRenderer(const glm::mat4& projMat)
{
    constexpr int num_dims = 2;
    _quad = Loader::loadToVao(VERTICES, num_dims);
    _shader = Shader("res/shaders/particle.vert", "res/shaders/particle.frag");
    _shader.use();
    _shader.setMatrix("projectionMatrix", projMat);
    _shader.stop();
}

void ParticleRenderer::render(const std::vector<Particle> &particles, const Camera &camera) {
    auto viewMatrix = Maths::createViewMatrix(camera);

    prepare();

	auto it = particles.cbegin();
    while (it != particles.cend()) {
        const Particle& particle = *it;
        updateModelViewMat(particle.getPosition(), particle.getRotation(),
            particle.getScale(), viewMatrix);
        glDrawArrays(GL_TRIANGLE_STRIP, 0, _quad.get_vertexCount());
        it++;
    }
    finishRendering();
}

void ParticleRenderer::prepare() {
    _shader.use();
    glBindVertexArray(_quad.get_vaoID());
    glEnableVertexAttribArray(0);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glDepthMask(GL_FALSE);
}

void ParticleRenderer::finishRendering() {
    glDepthMask(GL_TRUE);
    glDisable(GL_BLEND);
    glDisableVertexAttribArray(0);
    glBindVertexArray(0);
    _shader.stop();
}

void ParticleRenderer::updateModelViewMat(const glm::vec3 &position, float rotation, float scale,
                                          const glm::mat4 &viewMatrix) {
    glm::mat4 unit = glm::mat4 { 1.0f };
    glm::mat4 modelMatrix = glm::translate(unit, position);
    modelMatrix[0][0] = viewMatrix[0][0];
    modelMatrix[0][1] = viewMatrix[1][0];
    modelMatrix[0][2] = viewMatrix[2][0];
    modelMatrix[1][0] = viewMatrix[0][1];
    modelMatrix[1][1] = viewMatrix[1][1];
    modelMatrix[1][2] = viewMatrix[2][1];
    modelMatrix[2][0] = viewMatrix[0][2];
    modelMatrix[2][1] = viewMatrix[1][2];
    modelMatrix[2][2] = viewMatrix[2][2];
    modelMatrix = glm::rotate(modelMatrix, glm::radians(rotation), glm::vec3(0.0f, 0.0f, 1.0f));
    modelMatrix = glm::scale(modelMatrix, glm::vec3(scale));
    glm::mat4 modelViewMatrix = viewMatrix * modelMatrix;
    _shader.setMatrix("modelViewMatrix", modelViewMatrix);
}
