#ifndef RENDERENGINE_TERRAIN_H
#define RENDERENGINE_TERRAIN_H

#include <models/raw_model.h>
#include <textures/model_texture.h>

class Terrain {
public:
    Terrain(int gridX, int gridZ, const ModelTexture& tex);

private:
    const float SIZE = 800;
    const unsigned int VERTEX_COUNT = 128;

    float _x, _z;
public:
    float get_x() const;

    void set_x(float _x);

    float get_z() const;

    void set_z(float _z);

    const RawModel &get_model() const;

    void set_model(const RawModel &_model);

    const ModelTexture &get_texture() const;

    void set_texture(const ModelTexture &_texture);

private:
    RawModel _model;
    ModelTexture _texture;

    RawModel generateTerrain();

};


#endif //RENDERENGINE_TERRAIN_H