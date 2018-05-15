#ifndef RENDERENGINE_LOADER_H
#define RENDERENGINE_LOADER_H

#include <vector>
#include "models/raw_model.h"

class Loader {
public:
    static RawModel loadToVAO(std::vector<float> &positions, std::vector<unsigned int> &indices, std::vector<float> &normals,
                                  std::vector<float> &texCoords);
    static void cleanUp();
    static unsigned int loadTexture(const std::string &fileName);

private:
    static std::vector<unsigned int> _vaos;
    static std::vector<unsigned int> _vbos;
    static std::vector<unsigned int> _textures;

    static unsigned int createVAO();
    static unsigned int createVBO();
    static void storeData(unsigned int attNum, std::vector<float> &data, unsigned int coordSize);
    static void unbindVAO();
    static void bindIndicesBuffer(std::vector<unsigned int> &indices);
};


#endif //RENDERENGINE_LOADER_H
