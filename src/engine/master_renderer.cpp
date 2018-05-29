#include <utilities/maths.h>
#include <Log.h>
#include "master_renderer.h"
#include "entity_renderer.h"
#include "window_manager.h"
#include <skybox/skybox_renderer.h>
#include <terrain_renderer.h>

#include <glm/gtc/matrix_transform.hpp>

#include <algorithm>

glm::mat4 MasterRenderer::_projectionMatrix;
Shader MasterRenderer::_shader;
Shader MasterRenderer::_terrainShader;

std::vector<Terrain> MasterRenderer::_terrains;
std::map<TexturedModel, std::vector<Entity>> MasterRenderer::_entities;
std::map<TexturedModel, std::vector<Entity>> MasterRenderer::_normalMapEntities;

glm::vec3 MasterRenderer::_skyColour = glm::vec3(0.544f, 0.62f, 0.69f);
NormalMapRenderer MasterRenderer::_normalMapRenderer;

//some constants needed for the projection matrix
const float FOV = 70.f;
const float NEAR_PLANE = 1.f;
const float FAR_PLANE = 1000.f;
const int MAX_LIGHTS = 4;

void MasterRenderer::initialise() {
    //enable face culling so that not visible faces are not rendered
    enableCulling();
    _shader = Shader("res/shaders/basic.vert", "res/shaders/basic.frag");
    _terrainShader = Shader("res/shaders/terrain.vert", "res/shaders/terrain.frag");
    createProjectionMatrix();
    Renderer::initialise(_shader, _projectionMatrix);
    TerrainRenderer::initialise(_terrainShader, _projectionMatrix);
    SkyboxRenderer::initialise(_projectionMatrix);
    _normalMapRenderer = NormalMapRenderer(_projectionMatrix);
}

void MasterRenderer::prepare() {
    //enable depth test so that vertices can be drawn in the correct order
    glEnable(GL_DEPTH_TEST);
    //clear colour buffer and depth buffer
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    //set background colour
    glClearColor(_skyColour.x, _skyColour.y, _skyColour.z, 1.0f);
}

void MasterRenderer::cleanUp() {
    _shader.cleanUp();
    _terrainShader.cleanUp();
}

void MasterRenderer::renderScene(const std::vector<Entity> &entities, const std::vector<Entity> &normalMapEntities,
                                 const Terrain &terrain, std::vector<Light> &lights, Camera &cam, const Entity &player,
                                 const glm::vec4 &clipPlane) {

    processTerrain(terrain);

    for(const auto& ent : entities) {
        processEntity(ent);
    }

    for(const auto& ent : normalMapEntities) {
        processNormalMapEntity(ent);
    }

    processEntity(player);

    render(lights, cam, clipPlane);
}

void MasterRenderer::render(std::vector<Light> &lights, Camera &camera, const glm::vec4 &clipPlane) {
    //prepare for rendering
    prepare();

    sortLightsVector(lights, camera);

    //render entities
    _shader.use();
    _shader.setVec4("plane", clipPlane);
    _shader.setVec3("skyColour", _skyColour);
    for(int i = 0; i < MAX_LIGHTS; ++i) {
        auto index = i;
        //instead of loading a the last light, make sure the "sun" is loaded!
        if(i == MAX_LIGHTS - 1) {
            //due to the sorting, the sun should be at the end of the list
            index = static_cast<int>(lights.size() - 1);
        }
        _shader.setVec3("lightPosition[" + std::to_string(i) + "]", lights[index].getPosition());
        _shader.setVec3("lightColour[" + std::to_string(i) + "]", lights[index].getColour());
        _shader.setVec3("attenuation[" + std::to_string(i) + "]", lights[index].getAttenuation());
    }

    _shader.setMatrix("viewMatrix", Maths::createViewMatrix(camera));
    Renderer::render(_entities);
    _shader.stop();
    //----------------

    //render normal map entities
    _normalMapRenderer.render(_normalMapEntities, clipPlane, lights, camera);
    //-----

    //render terrain
    _terrainShader.use();
    _terrainShader.setVec4("plane", clipPlane);
    _terrainShader.setVec3("skyColour", _skyColour);
    for(int i = 0; i < MAX_LIGHTS; ++i) {
        auto index = i;
        if(i == MAX_LIGHTS - 1) {
            index = static_cast<int>(lights.size() - 1);
        }
        _terrainShader.setVec3("lightPosition[" + std::to_string(i) + "]", lights[index].getPosition());
        _terrainShader.setVec3("lightColour[" + std::to_string(i) + "]", lights[index].getColour());
        _terrainShader.setVec3("attenuation[" + std::to_string(i) + "]", lights[index].getAttenuation());
    }
    _terrainShader.setMatrix("viewMatrix", Maths::createViewMatrix(camera));
    TerrainRenderer::render(_terrains);
    _terrainShader.stop();
    //----------------

    //render skybox
    SkyboxRenderer::render(camera, _skyColour);
    //----------------

    _terrains.clear();
    _entities.clear();
    _normalMapEntities.clear();
}

void MasterRenderer::processEntity(const Entity &entity) {
    _entities[entity.getModel()].push_back(entity);
}

void MasterRenderer::processNormalMapEntity(const Entity &entity) {
    _normalMapEntities[entity.getModel()].push_back(entity);
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

const glm::mat4 &MasterRenderer::get_projectionMatrix() {
    return _projectionMatrix;
}

const glm::vec3 &MasterRenderer::get_skyColour() {
    return _skyColour;
}

void MasterRenderer::sortLightsVector(std::vector<Light> &lights, const Camera &camera) {
    //need this temporary light so that the vector can be sorted according to it
    Light tmp = Light(camera.getPlayerPosition(), glm::vec3(0, 0, 0));
    //sort the vector so that only the 4 closest lights are loaded to the shader
    //obviously not ideal as it's being sorted every frame
    std::sort(std::begin(lights), std::end(lights), DistanceFunc(tmp));
}



