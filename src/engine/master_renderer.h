#ifndef RENDERENGINE_MASTER_RENDERER_H
#define RENDERENGINE_MASTER_RENDERER_H

#include <models/textured_model.h>
#include <entities/entity.h>
#include <shaders/shader.h>
#include <entities/camera.h>
#include <entities/light.h>
#include <terrains/terrain.h>
#include "normal_map_renderer.h"

#include <map>
#include <vector>

class MasterRenderer {
public:
    static void prepare();
    static void initialise();
    static void cleanUp();
    static void render(std::vector<Light> &lights, Camera &camera, const glm::vec4 &clipPlane);
    static void renderScene(const std::vector<Entity> &entities, const std::vector<Entity> &normalMapEntities,
                                const Terrain &terrain, std::vector<Light> &lights, Camera &cam, const Entity &player,
                                const glm::vec4 &clipPlane);
    static void processEntity(const Entity& entity);
    static void processNormalMapEntity(const Entity& entity);
    static void processTerrain(const Terrain& terrain);
    static void createProjectionMatrix();
    static void enableCulling();
    static void disableCulling();

    static const glm::mat4 &get_projectionMatrix();

    static const glm::vec3 &get_skyColour();

private:
    static glm::mat4 _projectionMatrix;
    static Shader _shader, _terrainShader;
    static glm::vec3 _skyColour;
    static NormalMapRenderer _normalMapRenderer;

    static std::map<TexturedModel, std::vector<Entity>> _entities;
    static std::map<TexturedModel, std::vector<Entity>> _normalMapEntities;

    static std::vector<Terrain> _terrains;

    static void sortLightsVector(std::vector<Light> &lights, const Camera &camera);

    struct DistanceFunc
    {
        explicit DistanceFunc(const Light& _p) : p(_p) {}

        bool operator()(const Light& lhs, const Light& rhs) const
        {
            return Maths::euclideanDistance(p.getPosition(), lhs.getPosition()) < Maths::euclideanDistance(p.getPosition(), rhs.getPosition());
        }

    private:
        Light p;
    };

};


#endif //RENDERENGINE_MASTER_RENDERER_H
