#ifndef RENDERENGINE_WATER_RENDERER_H
#define RENDERENGINE_WATER_RENDERER_H

#include <models/raw_model.h>
#include <shaders/shader.h>
#include "water_tile.h"
#include "water_frame_buffers.h"
#include <entities/camera.h>
#include <entities/light.h>
#include <utilities/Log.h>

#include <glm/glm.hpp>

#include <vector>
#include <string>

class WaterRenderer {
public:
    WaterRenderer(const Shader &shader, const glm::mat4 &projMat, const WaterFrameBuffers &fbos);

    void render(const std::vector<WaterTile> &water, const Camera &camera, const Light &sun);

    ~WaterRenderer() = default;
private:
    const std::string DUDV_MAP = "waterDUDV";
    const std::string NORMAL_MAP = "waterNormalMap";
    const float WAVE_SPEED = 0.03f;

    RawModel _quad;
    Shader _shader;
    std::vector<float> _vertices;
    const WaterFrameBuffers& _fbos;
    unsigned int _dudvTexture;
    unsigned int _normalMapTexture;
    float _moveFactor = 0.f;

    void prepare(const Camera &camera, const Light &sun);
    void unbind();
    void initVertices();
};


#endif //RENDERENGINE_WATER_RENDERER_H
