#ifndef RENDERENGINE_MASTER_RENDERER_H
#define RENDERENGINE_MASTER_RENDERER_H

#include <models/textured_model.h>
#include <entities/entity.h>
#include <shaders/shader.h>
#include <entities/camera.h>
#include <entities/light.h>

#include <map>
#include <vector>
#include <terrains/terrain.h>

class MasterRenderer {
public:
    static void prepare();
    static void initialise();
    static void cleanUp();
    static void render(Light& light, Camera& camera);
    static void processEntity(const Entity& entity);
    static void processTerrain(const Terrain& terrain);
    static void createProjectionMatrix();
    static void enableCulling();
    static void disableCulling();

private:
    static glm::mat4 _projectionMatrix;
    static Shader _shader, _terrainShader;
    static glm::vec3 _skyColour;

    static std::map<TexturedModel, std::vector<Entity>> _entities;
    static std::vector<Terrain> _terrains;
};


#endif //RENDERENGINE_MASTER_RENDERER_H