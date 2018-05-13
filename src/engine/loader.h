#ifndef RENDERENGINE_LOADER_H
#define RENDERENGINE_LOADER_H

#include <vector>
#include "models/raw_model.h"

class Loader {
public:
    RawModel loadToVAO(vector<float> &positions, vector<unsigned int> &indices, vector<float> &texCoords);
    void cleanUp();
    unsigned int loadTexture(const std::string &fileName);

private:
    std::vector<unsigned int> _vaos;
    std::vector<unsigned int> _vbos;
    std::vector<unsigned int> _textures;

    unsigned int createVAO();
    unsigned int createVBO();
    void storeData(unsigned int attNum, vector<float> &data, unsigned int coordSize);
    void unbindVAO();
    void bindIndicesBuffer(vector<unsigned int> &indices);
};


#endif //RENDERENGINE_LOADER_H
