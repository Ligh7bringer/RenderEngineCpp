#include <utilities/maths.h>
#include <Log.h>
#include "master_renderer.h"
#include "entity_renderer.h"
#include "window_manager.h"

#include <glm/gtc/matrix_transform.hpp>
#include <terrain_renderer.h>

glm::mat4 MasterRenderer::_projectionMatrix;
Shader MasterRenderer::_shader;
Shader MasterRenderer::_terrainShader;

std::vector<Terrain> MasterRenderer::_terrains;
std::map<TexturedModel, std::vector<Entity>> MasterRenderer::_entities;

//some constants needed for the projection matrix
const float FOV = 70.f;
const float NEAR_PLANE = 0.1f;
const float FAR_PLANE = 1000.f;

void MasterRenderer::initialise() {
    //enable face culling so that not visible faces are not rendered
    enableCulling();
    _shader = Shader("res/shaders/basic.vert", "res/shaders/basic.frag");
    _terrainShader = Shader("res/shaders/terrain.vert", "res/shaders/terrain.frag");
    createProjectionMatrix();
    Renderer::initialise(_shader, _projectionMatrix);
    TerrainRenderer::initialise(_terrainShader, _projectionMatrix);
}

void MasterRenderer::prepare() {
    //enable depth test so that vertices can be drawn in the correct order
    glEnable(GL_DEPTH_TEST);
    //clear colour buffer and depth buffer
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    //set background colour
    glClearColor(0.0f, 0.5f, 0.5f, 1.0f);
}

void MasterRenderer::cleanUp() {
    _shader.cleanUp();
    _terrainShader.cleanUp();
}

void MasterRenderer::render(Light &light, Camera &camera) {
    prepare();

    _shader.use();
    _shader.setVector3("lightPosition", light.getPosition());
    _shader.setVector3("lightColour", light.getColour());
    _shader.setMatrix("viewMatrix", Maths::createViewMatrix(camera));
    Renderer::render(_entities);
    _shader.stop();

    _terrainShader.use();
    _terrainShader.setVector3("lightPosition", light.getPosition());
    _terrainShader.setVector3("lightColour", light.getColour());
    _terrainShader.setMatrix("viewMatrix", Maths::createViewMatrix(camera));
    TerrainRenderer::render(_terrains);
    _terrainShader.stop();

    _terrains.clear();
    _entities.clear();
}

void MasterRenderer::processEntity(const Entity &entity) {
    auto entModel = entity.getModel();
    _entities[entModel].push_back(entity);
}

//creates the projection matrix
void MasterRenderer::createProjectionMatrix() {
    //get window size
    auto winSize = WindowManager::getWindowSize();
    //calculate the matrix using the very convenient glm method
    _projectionMatrix = glm::perspectiveFov(glm::radians(FOV), winSize.x, winSize.y, NEAR_PLANE, FAR_PLANE);
}

void MasterRenderer::processTerrain(const Terrain &terrain) {
    _terrains.push_back(terrain);
}

void MasterRenderer::enableCulling() {
    glEnable(GL_CULL_FACE);
    glCullFace(GL_BACK);
}

void MasterRenderer::disableCulling() {
    glDisable(GL_CULL_FACE);
}

