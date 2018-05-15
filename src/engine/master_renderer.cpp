#include <utilities/maths.h>
#include <Log.h>
#include "master_renderer.h"
#include "renderer.h"

std::map<TexturedModel, std::vector<Entity>> MasterRenderer::_entities;
Shader MasterRenderer::_shader;

void MasterRenderer::cleanUp() {
    _shader.cleanUp();
}

void MasterRenderer::render(Light &light, Camera &camera) {
    Renderer::prepare();
    _shader.use();
    _shader.setVector3("lightPosition", light.getPosition());
    _shader.setVector3("lightColour", light.getColour());
    _shader.setMatrix("viewMatrix", Maths::createViewMatrix(camera));
    Renderer::render(_entities);
    _shader.stop();
    _entities.clear();
}

void MasterRenderer::processEntity(const Entity &entity) {
    auto entModel = entity.getModel();
    _entities[entModel].push_back(entity);
}

void MasterRenderer::initialise() {
    _shader = Shader("res/shaders/basic.vert", "res/shaders/basic.frag");
    Renderer::initialise(_shader);
}

