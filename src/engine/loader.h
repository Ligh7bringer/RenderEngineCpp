#ifndef RENDERENGINE_LOADER_H
#define RENDERENGINE_LOADER_H

#include <vector>
#include "models/raw_model.h"

class Loader {
private:
    std::vector<unsigned int> _vaos;
    std::vector<unsigned int> _vbos;

    unsigned int createVAO();
    unsigned int createVBO();
    void storeData(unsigned int attNum, float data[], int count);
    void unbindVAO();

public:
    RawModel loadToVAO(float positions[], int count);
    void cleanUp();

};


#endif //RENDERENGINE_LOADER_H
