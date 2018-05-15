#ifndef RENDERENGINE_MASTER_RENDERER_H
#define RENDERENGINE_MASTER_RENDERER_H

#include <models/textured_model.h>
#include <entities/entity.h>
#include <shaders/shader.h>
#include <entities/camera.h>
#include <entities/light.h>

#include <map>
#include <vector>

class MasterRenderer {
public:
    static void initialise();
    static void cleanUp();
    static void render(Light& light, Camera& camera);
    static void processEntity(const Entity& entity);

private:
    static std::map<TexturedModel, std::vector<Entity>> _entities;
    static Shader _shader;
};


#endif //RENDERENGINE_MASTER_RENDERER_H
