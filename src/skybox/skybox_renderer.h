#ifndef RENDERENGINE_SKYBOX_RENDERER_H
#define RENDERENGINE_SKYBOX_RENDERER_H

#include <vector>
#include <string>

#include <models/raw_model.h>
#include <shaders/shader.h>
#include <entities/camera.h>

class SkyboxRenderer {
public:
    static void initialise(const glm::mat4& projMat);
    static void render(const Camera& cam);

private:
    static float SIZE;
    static std::vector<float> VERTICES;
    static std::vector<std::string> TEXTURES;
    static RawModel _model;
    static unsigned int _texture;
    static Shader _shader;
};


#endif //RENDERENGINE_SKYBOX_RENDERER_H
