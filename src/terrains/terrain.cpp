#include "terrain.h"
#include <engine/loader.h>

#include <vector>

#include <stb_image.h>
#include <glm/glm.hpp>
#include <Log.h>
#include <glad/glad.h>
#include <utilities/maths.h>

Terrain::Terrain(int gridX, int gridZ, const TerrainTexturePack &pack, const TerrainTexture &blendMap,
                 const std::string &heightmap) :
        _x(gridX), _z(gridZ), _model(generateTerrain(heightmap)),
        _texturePack(pack), _blendMap(blendMap)
{}

RawModel Terrain::generateTerrain(const std::string &fileName) {
    auto img = Image(fileName);
    auto VERTEX_COUNT = img.getHeight();
    _heights.resize(VERTEX_COUNT);
    for (auto& height : _heights)
        height.resize(VERTEX_COUNT);

    auto count = VERTEX_COUNT * VERTEX_COUNT;
    auto vertices = std::vector<float>(count * 3);
    auto normals = std::vector<float>(count * 3);
    auto texCoords = std::vector<float>(count * 2);
    auto indices = std::vector<unsigned int>(6 * (VERTEX_COUNT-1)*(VERTEX_COUNT-1));

    int vertexPointer = 0;
    for(int i = 0; i < VERTEX_COUNT; ++i) {
        for(int j = 0; j < VERTEX_COUNT; ++j) {
            vertices[vertexPointer*3] = (float)j/((float)VERTEX_COUNT - 1) * SIZE;
            auto height = getHeight(j, i, img);
            _heights[j][i] = height;
            vertices[vertexPointer*3+1] = height;
            vertices[vertexPointer*3+2] = (float)i/((float)VERTEX_COUNT - 1) * SIZE;
            auto normal = calculateNormal(j, i, img);
            normals[vertexPointer*3] = normal.x;
            normals[vertexPointer*3+1] = normal.y;
            normals[vertexPointer*3+2] = normal.z;
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

float Terrain::getHeight(float x, float y, const Image &image) {
    if(x < 0 || y < 0) {
        return 0;
    }

    auto height = static_cast<float>(image.getRGBSum(x, y));
    height /= (MAX_PIXEL_COLOUR/2);
    height -= 1.0;
    height *= MAX_HEIGHT;

    return height;
}

glm::vec3 Terrain::calculateNormal(int x, int z, Image &img) {
    float heightL = getHeight(x-1, z, img);
    float heightR = getHeight(x+1, z, img);
    float heightD = getHeight(x, z-1, img);
    float heightU = getHeight(x, z+1, img);
    glm::vec3 normal = {
            heightL - heightR,
            2.f,
            heightD - heightU
    };

    normal = glm::normalize(normal);
    return normal;
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

const TerrainTexturePack &Terrain::get_texturePack() const {
    return _texturePack;
}

const TerrainTexture &Terrain::get_blendMap() const {
    return _blendMap;
}

float Terrain::getHeightOfTerrain(float worldX, float worldZ) const {
    auto terrainX = worldX - _x;
    auto terrainZ = worldZ - _z;
    float gridSquareSize = SIZE / static_cast<float>(_heights.size() - 1);
    auto gridX = static_cast<int>(std::floor(terrainX / gridSquareSize));
    auto gridZ = static_cast<int>(std::floor(terrainZ / gridSquareSize));

    if(gridX >= _heights.size() - 1 || gridZ >= _heights.size() - 1 || gridX < 0 || gridZ < 0) {
        return 0.f;
    }

    float xCoord = std::fmod(terrainX, gridSquareSize) / gridSquareSize;
    float zCoord = std::fmod(terrainZ, gridSquareSize) / gridSquareSize;
    float answer;
    if(xCoord <= (1.f - zCoord)) {
        answer = Maths::barryCentricInterpolation(glm::vec3{0, _heights[gridX][gridZ], 0},
                                                  glm::vec3{1, _heights[gridX + 1][gridZ], 0},
                                                  glm::vec3{0, _heights[gridX][gridZ + 1], 1},
                                                  glm::vec2{xCoord, zCoord});
    } else {
        answer = Maths::barryCentricInterpolation(glm::vec3{0, _heights[gridX + 1][gridZ], 0},
                                                  glm::vec3{1, _heights[gridX + 1][gridZ + 1], 1},
                                                  glm::vec3{0, _heights[gridX][gridZ + 1], 1},
                                                  glm::vec2{xCoord, zCoord});
    }

    return answer;
}

