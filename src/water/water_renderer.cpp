#include "water_renderer.h"
#include "water_frame_buffers.h"

#include <engine/loader.h>
#include <utilities/maths.h>
#include <engine/window_manager.h>

#include <vector>
#include <cmath>

WaterRenderer::WaterRenderer(const Shader &shader, const glm::mat4 &projMat, const WaterFrameBuffers &fbos) :
        _shader(shader), _fbos(fbos) {

    auto dudvImg = Image(DUDV_MAP);
    auto nmapImg = Image(NORMAL_MAP);
    _dudvTexture = dudvImg.getID();
    _normalMapTexture = nmapImg.getID();
    initVertices();
    _quad = Loader::loadToVao(_vertices, 2);
    _shader.use();
    _shader.setInt("reflectionTexture", 0);
    _shader.setInt("refractionTexture", 1);
    _shader.setInt("dudvMap", 2);
    _shader.setInt("normalMap", 3);
    _shader.setInt("depthMap", 4);
    _shader.setMatrix("projectionMatrix", projMat);
    _shader.stop();
}

void WaterRenderer::render(const std::vector<WaterTile> &water, const Camera &camera, const Light &sun) {
    prepare(camera, sun);

    for(const auto& tile : water) {
        auto modelMatrix = Maths::createTransformationMatrix(glm::vec3(tile.getX(), tile.getHeight(), tile.getZ()),
                glm::vec3(0, 0, 0), tile.getTileSize());
        _shader.setMatrix("modelMatrix", modelMatrix);
        glDrawArrays(GL_TRIANGLES, 0, _quad.get_vertexCount());
    }

    unbind();
}

void WaterRenderer::prepare(const Camera &camera, const Light &sun) {
    _shader.use();
    _shader.setMatrix("viewMatrix", Maths::createViewMatrix(camera));
    _shader.setVec3("cameraPos", camera.getPosition());

    _moveFactor += WAVE_SPEED * WindowManager::getDeltaTime();
    _moveFactor = static_cast<float>(std::fmod(_moveFactor, 1));

    _shader.setFloat("moveFactor", _moveFactor);
    _shader.setVec3("lightColour", sun.getColour());
    _shader.setVec3("lightPosition", sun.getPosition());

    glBindVertexArray(_quad.get_vaoID());
    glEnableVertexAttribArray(0);

    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, _fbos.getReflectionTexture());
    glActiveTexture(GL_TEXTURE1);
    glBindTexture(GL_TEXTURE_2D, _fbos.getRefractionTexture());
    glActiveTexture(GL_TEXTURE2);
    glBindTexture(GL_TEXTURE_2D, _dudvTexture);
    glActiveTexture(GL_TEXTURE3);
    glBindTexture(GL_TEXTURE_2D, _normalMapTexture);
    glActiveTexture(GL_TEXTURE4);
    glBindTexture(GL_TEXTURE_2D, _fbos.getRefractionDepthTexture());

    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
}

void WaterRenderer::unbind() {
    glDisable(GL_BLEND);
    glDisableVertexAttribArray(0);
    glBindVertexArray(0);
    _shader.stop();
}

void WaterRenderer::initVertices() {
    _vertices =  { -1, -1, -1, 1, 1, -1, 1, -1, -1, 1, 1, 1 };
}

