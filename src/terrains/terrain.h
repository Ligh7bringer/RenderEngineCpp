#ifndef RENDERENGINE_TERRAIN_H
#define RENDERENGINE_TERRAIN_H

#include <models/raw_model.h>
#include <textures/model_texture.h>
#include <textures/terrain_texture_pack.h>
#include <textures/image.h>

#include <string>
#include <vector>

class Terrain {
public:
    Terrain(int gridX, int gridZ, const TerrainTexturePack &pack, const TerrainTexture &blendMap,
                const std::string &heightmap);

    float getHeightOfTerrain(float worldX, float worldZ) const;

    float get_x() const;
    void set_x(float _x);
    float get_z() const;
    void set_z(float _z);
    const RawModel &get_model() const;
    const TerrainTexturePack &get_texturePack() const;
    const TerrainTexture &get_blendMap() const;

private:
    const float SIZE = 800;
    const float MAX_HEIGHT = 40.f;
    const float MIN_HEIGHT = -40.f;
    const float MAX_PIXEL_COLOUR = 256 * 256 * 256;

    float _x, _z;
    std::vector<std::vector<float>> _heights;
    RawModel _model;
    TerrainTexturePack _texturePack;
    TerrainTexture _blendMap;

    RawModel generateTerrain(const std::string &fileName);
    float getHeight(float x, float y, const Image &image);
    glm::vec3 calculateNormal(int x, int z, Image &img);
};


#endif //RENDERENGINE_TERRAIN_H