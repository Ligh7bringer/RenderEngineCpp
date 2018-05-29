#ifndef RENDERENGINE_NORMAL_MAP_RENDERER_H
#define RENDERENGINE_NORMAL_MAP_RENDERER_H

#include <glm/glm.hpp>

#include <models/textured_model.h>
#include <entities/entity.h>
#include <entities/light.h>
#include <entities/camera.h>
#include <shaders/shader.h>

#include <vector>
#include <map>

class NormalMapRenderer {
public:
    NormalMapRenderer() = default;
    explicit NormalMapRenderer(const glm::mat4& projMat);

    void render(const std::map<TexturedModel, std::vector<Entity>> &entities, const glm::vec4 &clipPlane,
                const std::vector<Light> &lights, const Camera &camera);

private:
    Shader _shader;

    void prepareModel(const TexturedModel& model);
    void unbindModel();
    void prepareInstance(const Entity& entity);
    void prepare(const glm::vec4& clipPlane, const std::vector<Light>& lights, const Camera& camera);
    glm::vec3 calculateEyeSpacePos(const Light& light, const glm::mat4& viewMatrix);
};


#endif //RENDERENGINE_NORMAL_MAP_RENDERER_H
