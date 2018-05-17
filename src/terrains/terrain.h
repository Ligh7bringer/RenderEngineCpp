#ifndef RENDERENGINE_TERRAIN_H
#define RENDERENGINE_TERRAIN_H

#include <models/raw_model.h>
#include <textures/model_texture.h>
#include <textures/terrain_texture_pack.h>

class Terrain {
public:
    Terrain(int gridX, int gridZ, const TerrainTexturePack& pack, const TerrainTexture& blendMap);

    float get_x() const;

    void set_x(float _x);

    float get_z() const;

    void set_z(float _z);

    const RawModel &get_model() const;

    const TerrainTexturePack &get_texturePack() const;

    const TerrainTexture &get_blendMap() const;

private:
    const float SIZE = 800;
    const unsigned int VERTEX_COUNT = 128;

    float _x, _z;

    RawModel _model;
    TerrainTexturePack _texturePack;
    TerrainTexture _blendMap;

    RawModel generateTerrain();

};


#endif //RENDERENGINE_TERRAIN_H