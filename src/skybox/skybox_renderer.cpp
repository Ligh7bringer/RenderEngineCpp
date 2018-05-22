#include "skybox_renderer.h"
#include <engine/loader.h>
#include <utilities/maths.h>
#include <Log.h>

float SkyboxRenderer::SIZE = 500.f;
std::vector<float> SkyboxRenderer::VERTICES = {
        -SIZE,  SIZE, -SIZE,
        -SIZE, -SIZE, -SIZE,
        SIZE, -SIZE, -SIZE,
        SIZE, -SIZE, -SIZE,
        SIZE,  SIZE, -SIZE,
        -SIZE,  SIZE, -SIZE,

        -SIZE, -SIZE,  SIZE,
        -SIZE, -SIZE, -SIZE,
        -SIZE,  SIZE, -SIZE,
        -SIZE,  SIZE, -SIZE,
        -SIZE,  SIZE,  SIZE,
        -SIZE, -SIZE,  SIZE,

        SIZE, -SIZE, -SIZE,
        SIZE, -SIZE,  SIZE,
        SIZE,  SIZE,  SIZE,
        SIZE,  SIZE,  SIZE,
        SIZE,  SIZE, -SIZE,
        SIZE, -SIZE, -SIZE,

        -SIZE, -SIZE,  SIZE,
        -SIZE,  SIZE,  SIZE,
        SIZE,  SIZE,  SIZE,
        SIZE,  SIZE,  SIZE,
        SIZE, -SIZE,  SIZE,
        -SIZE, -SIZE,  SIZE,

        -SIZE,  SIZE, -SIZE,
        SIZE,  SIZE, -SIZE,
        SIZE,  SIZE,  SIZE,
        SIZE,  SIZE,  SIZE,
        -SIZE,  SIZE,  SIZE,
        -SIZE,  SIZE, -SIZE,

        -SIZE, -SIZE, -SIZE,
        -SIZE, -SIZE,  SIZE,
        SIZE, -SIZE, -SIZE,
        SIZE, -SIZE, -SIZE,
        -SIZE, -SIZE,  SIZE,
        SIZE, -SIZE,  SIZE
};

std::vector<std::string> SkyboxRenderer::TEXTURES = { "right", "left", "top", "bottom", "back", "front" };
RawModel SkyboxRenderer::_model;
unsigned int SkyboxRenderer::_texture;
Shader SkyboxRenderer::_shader;

void SkyboxRenderer::initialise(const glm::mat4 &projMat) {
    _model = Loader::loadToVao(VERTICES, 3);
    _texture = Loader::loadCubeMap(TEXTURES);
    _shader = Shader("res/shaders/skybox.vert", "res/shaders/skybox.frag");
    _shader.use();
    _shader.setMatrix("projectionMatrix", projMat);
    _shader.stop();
}

void SkyboxRenderer::render(const Camera &cam) {
    _shader.use();
    _shader.setMatrix("viewMatrix", Maths::createSkyboxViewMatrix(cam));

    glBindVertexArray(_model.get_vaoID());
    glEnableVertexAttribArray(0);

    glBindVertexArray(_model.get_vaoID());
    glEnableVertexAttribArray(0);
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_CUBE_MAP, _texture);
    glDrawArrays(GL_TRIANGLES, 0, _model.get_vertexCount());

    glDisableVertexAttribArray(0);
    glBindVertexArray(0);

    _shader.stop();
}




