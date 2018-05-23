#include "skybox_renderer.h"
#include <engine/loader.h>
#include <utilities/maths.h>
#include <Log.h>
#include <engine/window_manager.h>
#include <glm/gtc/matrix_transform.hpp>
#include <utilities/gl_error.h>

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
std::vector<std::string> SkyboxRenderer::NIGHT_TEXTURES = { "nightRight", "nightLeft", "nightTop", "nightBottom", "nightBack", "nightFront" };
RawModel SkyboxRenderer::_model;
unsigned int SkyboxRenderer::_texture;
unsigned int SkyboxRenderer::_nightTexture;
Shader SkyboxRenderer::_shader;
float SkyboxRenderer::_rotation = 0.f;
float SkyboxRenderer::_timer = 0.f;

const float ROTATION_SPEED = 1.f;

void SkyboxRenderer::initialise(const glm::mat4 &projMat) {
    _model = Loader::loadToVao(VERTICES, 3);
    _texture = Loader::loadCubeMap(TEXTURES);
    _nightTexture = Loader::loadCubeMap(NIGHT_TEXTURES);
    _shader = Shader("res/shaders/skybox.vert", "res/shaders/skybox.frag");
    _shader.use();
    _shader.setInt("cubeMap", 0);
    _shader.setInt("cubeMap2", 1);
    _shader.setMatrix("projectionMatrix", projMat);
    _shader.stop();
}

void SkyboxRenderer::render(const Camera &cam, const glm::vec3 &fogColour) {
    _shader.use();

    auto viewMatrix = Maths::createSkyboxViewMatrix(cam);
    _rotation += ROTATION_SPEED * WindowManager::getDeltaTime();
    viewMatrix = glm::rotate(viewMatrix, glm::radians(_rotation), {0, 1, 0});
    _shader.setMatrix("viewMatrix", viewMatrix);

    _shader.setVec3("fogColour", fogColour);

    glBindVertexArray(_model.get_vaoID());
    glEnableVertexAttribArray(0);

    glBindVertexArray(_model.get_vaoID());
    glEnableVertexAttribArray(0);
    bindTextures();
    glDrawArrays(GL_TRIANGLES, 0, _model.get_vertexCount());

    glDisableVertexAttribArray(0);
    glBindVertexArray(0);

    _shader.stop();
}

void SkyboxRenderer::bindTextures() {
    _timer += WindowManager::getDeltaTime() * 1000.f;
    auto blendFactor = (std::sin(glm::radians(_timer / 100.f)) + 1.f) / 2.f;

    //bind day time textures to texture unit 0
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_CUBE_MAP, _texture);

    //bind night time textures to texture unit 1
    glActiveTexture(GL_TEXTURE1);
    glBindTexture(GL_TEXTURE_CUBE_MAP, _nightTexture);

    _shader.setFloat("blendFactor", blendFactor);
}




