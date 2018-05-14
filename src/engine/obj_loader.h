#ifndef RENDERENGINE_OBJ_LOADER_H
#define RENDERENGINE_OBJ_LOADER_H

#include <string>
#include <vector>

#include <models/raw_model.h>
#include <glm/vec3.hpp>
#include <glm/vec2.hpp>

class OBJLoader {
public:
    static RawModel loadModel(const std::string& fileName);

private:
    static bool startsWith(const std::string& line, const std::string& pref);
    static std::vector<std::string> split(const std::string &phrase, const std::string &delimiter);
    static void processVertex(const std::vector<std::string> &vertexData, std::vector<glm::vec2> &textures,
                                 std::vector<glm::vec3> &normals);

    static std::vector<float> _verticesArray;
    static std::vector<float> _texsArray;
    static std::vector<float> _normalsArray;
    static std::vector<unsigned int > _indices;
};


#endif //RENDERENGINE_OBJ_LOADER_H
