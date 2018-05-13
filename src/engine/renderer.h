#ifndef RENDERENGINE_RENDERER_H
#define RENDERENGINE_RENDERER_H

#include <models/textured_model.h>
#include <entities/entity.h>
#include <shaders/shader.h>
#include "models/raw_model.h"

class Renderer {
public:
    Renderer(Shader &shader);
    void prepare();
    void render(const Entity &entity, const Shader &shader);

private:
    glm::mat4 _projectionMatrix;

    void createProjectionMatrix();
};


#endif //RENDERENGINE_RENDERER_H
