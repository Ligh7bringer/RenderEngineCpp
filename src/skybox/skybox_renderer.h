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
    static void render(const Camera &cam, const glm::vec3 &fogColour);

private:
    static float SIZE;
    static std::vector<float> VERTICES;
    static std::vector<std::string> TEXTURES;
    static std::vector<std::string> NIGHT_TEXTURES;
    static RawModel _model;
    static unsigned int _texture;
    static unsigned int _nightTexture;
    static Shader _shader;
    static float _rotation;
    static float _timer;

    static void bindTextures();
};


#endif //RENDERENGINE_SKYBOX_RENDERER_H
