#include "obj_loader.h"
#include "loader.h"
#include <Log.h>

#include <algorithm>
#include <fstream>
#include <iterator>

const std::string MODEL_DIR = "res/models/";

std::vector<float> OBJLoader::_verticesArray;
std::vector<float> OBJLoader::_texsArray;
std::vector<float> OBJLoader::_normalsArray;
std::vector<unsigned int> OBJLoader::_indices;

RawModel OBJLoader::loadModel(const std::string &fileName) {
    _verticesArray.clear();
    _texsArray.clear();
    _normalsArray.clear();
    _indices.clear();

    auto loc = MODEL_DIR + fileName + ".obj";
    std::ifstream in(loc);

    if(!in.is_open()) {
        LOG(ERR) << "Couldn't load file " << loc << "!";
        //return RawModel(0, 0);
    }

    std::vector<glm::vec3> vertices;
    std::vector<glm::vec2> textures;
    std::vector<glm::vec3> normals;

    std::string line;
    while(getline(in, line)) {
        auto currLine = split(line, " ");
        if(startsWith(line, "v ")) {
            //LOG(DEBUG) << currLine[1] << ", " << currLine[2] << ", " << currLine[3];
            glm::vec3 vertex(std::stof(currLine[1]), std::stof(currLine[2]), stof(currLine[3]));
            vertices.emplace_back(vertex);
        } else if(startsWith(line, "vt ")) {
            glm::vec2 tex(std::stof(currLine[1]), std::stof(currLine[2]));
            textures.emplace_back(tex);
        } else if(startsWith(line, "vn ")) {
            glm::vec3 normal(std::stof(currLine[1]), std::stof(currLine[2]), stof(currLine[3]));
            normals.emplace_back(normal);
        } else if(startsWith(line, "f ")) {
            _texsArray.resize(vertices.size() * 2);
            _normalsArray.resize(vertices.size() * 3);

            break;
        }
    }

    while(!line.empty()) {
        if (!startsWith(line, "f ")) {
            std::getline(in, line);
            continue;
        }

        auto current_line = split(line, " ");
        auto vertex1 = split(current_line.at(1), "/");
        auto vertex2 = split(current_line.at(2), "/");
        auto vertex3 = split(current_line.at(3), "/");

        processVertex(vertex1, textures, normals);
        processVertex(vertex2, textures, normals);
        processVertex(vertex3, textures, normals);

        std::getline(in, line);
    }

    in.close();

    _verticesArray.reserve(vertices.size() * 3);
    for (const auto& vertex : vertices) {
        _verticesArray.push_back(vertex.x);
        _verticesArray.push_back(vertex.y);
        _verticesArray.push_back(vertex.z);
    }

    return Loader::loadToVAO(_verticesArray, _indices, _texsArray);
}

void OBJLoader::processVertex(const std::vector<std::string> &vertexData, std::vector<glm::vec2> &textures,
                             std::vector<glm::vec3> &normals) {
    int current_vertex_pointer = std::stoi(vertexData.at(0)) - 1;
    _indices.emplace_back(current_vertex_pointer);

    auto currTex = textures.at(std::stoi(vertexData[1]) - 1);
    _texsArray.at(current_vertex_pointer * 2) = currTex.x;
    _texsArray.at(current_vertex_pointer * 2 + 1) = 1 - currTex.y;

    auto currNorm = normals.at(std::stoi(vertexData[2]) - 1);
    _normalsArray.at(current_vertex_pointer*3) = currNorm.x;
    _normalsArray.at(current_vertex_pointer*3 + 1) = currNorm.y;
    _normalsArray.at(current_vertex_pointer*3 + 2) = currNorm.z;
}

bool OBJLoader::startsWith(const std::string &line, const std::string &pref) {
    return std::equal(pref.begin(), pref.end(), line.begin());
}

std::vector<std::string> OBJLoader::split(const string &phrase, const std::string &delimiter) {
    vector<string> list;
    string s = string(phrase);
    size_t pos = 0;
    string token;
    while ((pos = s.find(delimiter)) != string::npos) {
        token = s.substr(0, pos);
        list.push_back(token);
        s.erase(0, pos + delimiter.length());
    }
    list.push_back(s);

    return list;
}


