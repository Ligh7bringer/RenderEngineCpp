#ifndef RENDERENGINE_TERRAIN_RENDERER_H
#define RENDERENGINE_TERRAIN_RENDERER_H

#include <shaders/shader.h>
#include <terrains/terrain.h>

#include <vector>

class TerrainRenderer {
public:
    static void initialise(const Shader &shader, const glm::mat4 &projMat);
    static void render(const std::vector<Terrain>& terrains);

private:
    static Shader _shader;

    static void prepareTerrain(const Terrain &terrain);
    static void unbindTexturedModel();
    static void prepareInstance(const Terrain &terrain);
};


#endif //RENDERENGINE_TERRAIN_RENDERER_H
