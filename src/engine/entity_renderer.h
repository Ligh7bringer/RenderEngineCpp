#ifndef RENDERENGINE_RENDERER_H
#define RENDERENGINE_RENDERER_H

#include <models/textured_model.h>
#include <entities/entity.h>
#include <shaders/shader.h>
#include "models/raw_model.h"

#include <map>
#include <vector>

class Renderer {
public:
    static void initialise(Shader &shader, const glm::mat4 &projMat);
    static void render(const std::map<TexturedModel, std::vector<Entity>>& entities);

private:
    static Shader _shader;

    static void prepareTexturedModel(const TexturedModel& model);
    static void unbindTexturedModel();
    static void prepareInstance(const Entity& entity);

};


#endif //RENDERENGINE_RENDERER_H
