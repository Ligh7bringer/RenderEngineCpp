#ifndef RENDERENGINE_LOADER_H
#define RENDERENGINE_LOADER_H

#include <vector>
#include <string>

#include <textures/image.h>
#include "models/raw_model.h"

#include <glad/glad.h>

class Loader {
public:
    static RawModel loadToVAO(std::vector<float> &positions, std::vector<unsigned int> &indices, std::vector<float> &normals,
                                  std::vector<float> &texCoords);
    static RawModel loadToVao(std::vector<glm::vec3> &positions, std::vector<unsigned int> &indices,
                                 std::vector<glm::vec3> &normals, std::vector<glm::vec2> &texCoords,
                                 std::vector<glm::vec3> &tangents);
    static RawModel loadToVao(std::vector<glm::vec3> &positions, std::vector<unsigned int> &indices,
                              std::vector<glm::vec3> &normals, std::vector<glm::vec2> &texCoords);
    static RawModel loadToVao(std::vector<float> &positions, int dimensions);
    static void cleanUp();
    static unsigned int loadTexture(const std::string &fileName);
    static unsigned int loadCubeMap(const std::vector<std::string>& fileNames);

private:
    static std::vector<unsigned int> _vaos;
    static std::vector<unsigned int> _vbos;
    static std::vector<unsigned int> _textures;

    static unsigned int createVAO();
    static unsigned int createVBO();
    static void unbindVAO();
    static void bindIndicesBuffer(std::vector<unsigned int> &indices);

    template <typename T>
    static void storeData(unsigned int attNum, unsigned int count, const std::vector<T>& data) {
            //create a vbo
            auto vboID = createVBO();
            //store it for later
            _vbos.push_back(vboID);
            //bind it so it can be used
            glBindBuffer(GL_ARRAY_BUFFER, vboID);
            //store data in the vbo: type of buffer, size, actual data, draw type
            //NOTE: &data.front() returns a pointer to the beginning of the vector, so it's like passing an array which is exactly what openGL is expecting
            glBufferData(GL_ARRAY_BUFFER, sizeof(T) * data.size(), &data.front(), GL_STATIC_DRAW);
            //put vbo into the vao: num of attribute list, length of vertex, type of data, distance between vertices, offset from start
            glVertexAttribPointer(attNum, count, GL_FLOAT, GL_FALSE, 0, nullptr);
            //unbind the vbo, 0 unbinds the current one
            glBindBuffer(GL_ARRAY_BUFFER, 0);
    }

};


#endif //RENDERENGINE_LOADER_H
