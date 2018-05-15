#include "terrain.h"
#include <engine/loader.h>

#include <vector>

Terrain::Terrain(int gridX, int gridZ, const ModelTexture &tex) : _texture(tex), _model(generateTerrain()) {
    _x = gridX;
    _z = gridZ;
}

RawModel Terrain::generateTerrain() {
    auto count = VERTEX_COUNT * VERTEX_COUNT;
    auto vertices = std::vector<float>(count * 3);
    auto normals = std::vector<float>(count * 3);
    auto texCoords = std::vector<float>(count * 2);
    auto indices = std::vector<unsigned int>(6 * (VERTEX_COUNT-1)*(VERTEX_COUNT-1));

    int vertexPointer = 0;
    for(int i = 0; i < VERTEX_COUNT; ++i) {
        for(int j = 0; j < VERTEX_COUNT; ++j) {
            vertices[vertexPointer*3] = (float)j/((float)VERTEX_COUNT - 1) * SIZE;
            vertices[vertexPointer*3+1] = 0;
            vertices[vertexPointer*3+2] = (float)i/((float)VERTEX_COUNT - 1) * SIZE;
            normals[vertexPointer*3] = 0;
            normals[vertexPointer*3+1] = 1;
            normals[vertexPointer*3+2] = 0;
            texCoords[vertexPointer*2] = (float)j/((float)VERTEX_COUNT - 1);
            texCoords[vertexPointer*2+1] = (float)i/((float)VERTEX_COUNT - 1);
            vertexPointer++;
        }
    }

    int pointer = 0;
    for(int gz=0;gz<VERTEX_COUNT-1;gz++){
        for(int gx=0;gx<VERTEX_COUNT-1;gx++){
            unsigned int topLeft = (gz*VERTEX_COUNT)+gx;
            unsigned int topRight = topLeft + 1;
            unsigned int bottomLeft = ((gz+1)*VERTEX_COUNT)+gx;
            unsigned int bottomRight = bottomLeft + 1;
            indices[pointer++] = topLeft;
            indices[pointer++] = bottomLeft;
            indices[pointer++] = topRight;
            indices[pointer++] = topRight;
            indices[pointer++] = bottomLeft;
            indices[pointer++] = bottomRight;
        }
    }

    return Loader::loadToVAO(vertices, indices, normals, texCoords);
}

// -- getters and setters -------
float Terrain::get_x() const {
    return _x;
}

void Terrain::set_x(float _x) {
    Terrain::_x = _x;
}

float Terrain::get_z() const {
    return _z;
}

void Terrain::set_z(float _z) {
    Terrain::_z = _z;
}

const RawModel &Terrain::get_model() const {
    return _model;
}

void Terrain::set_model(const RawModel &_model) {
    Terrain::_model = _model;
}

const ModelTexture &Terrain::get_texture() const {
    return _texture;
}

void Terrain::set_texture(const ModelTexture &_texture) {
    Terrain::_texture = _texture;
}
