#ifndef RENDERENGINE_OBJ_LOADER_H
#define RENDERENGINE_OBJ_LOADER_H

#include <string>
#include <vector>
#include <unordered_map>

#include <glm/glm.hpp>

#include <models/raw_model.h>

class OBJLoader {
public:
    static RawModel loadModel(const std::string& fileName);
    static RawModel LOAD(const std::string& fileName);

    struct Vertex {
        glm::vec3 pos;
        glm::vec2 texCoord;
        glm::vec3 normal;
    };

private:
    static bool startsWith(const std::string& line, const std::string& pref);
    static std::vector<std::string> split(const std::string &phrase, const std::string &delimiter);
    static void processVertex(const std::vector<std::string> &vertexData, std::vector<glm::vec2> &textures,
                                 std::vector<glm::vec3> &normals);

    static std::vector<float> _verticesArray;
    static std::vector<float> _texsArray;
    static std::vector<float> _normalsArray;
    static std::vector<unsigned int > _indices;
//    static bool vec2equals(const glm::vec& lhs, const glm::vec2& rhs); //why == is not overloaded for vectors is beyond me!
//    static bool vec3equals(const glm::vec3& lhs, const glm::vec3& rhs);
};

#endif //RENDERENGINE_OBJ_LOADER_H
