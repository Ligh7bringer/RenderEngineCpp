#include <glad/glad.h>
#include "loader.h"

//creates a raw model with the passed vertices
RawModel Loader::loadToVAO(float positions[], int count) {
    //create a vertex array
    unsigned int vaoID = createVAO();
    //store the data, starting from index 0
    storeData(0, positions, count);
    unbindVAO();

    //create and return the model
    return RawModel(vaoID, sizeof(positions));
}

unsigned int Loader::createVAO() {
    unsigned int vaoID;
    //create a vao and store its ID in vaoID
    glGenVertexArrays(1, &vaoID);
    //store it so it can be deleted later
    _vaos.push_back(vaoID);
    //bind it so it can be used
    glBindVertexArray(vaoID);

    return vaoID;
}

unsigned int Loader::createVBO() {
    unsigned int vboID;
    //create a vbo and store its ID in vboID
    glGenBuffers(1, &vboID);

    return vboID;
}

void Loader::unbindVAO() {
    //when 0 is passed, the current vao is unbound
    glBindVertexArray(0);
}

void Loader::storeData(unsigned int attNum, float data[], int count) {
    //create a vbo
    auto vboID = createVBO();
    //store it for later
    _vbos.push_back(vboID);
    //bind it so it can be used
    glBindBuffer(GL_ARRAY_BUFFER, vboID);
    //store data in the vbo: type of buffer, size, actual data, draw type
    glBufferData(GL_ARRAY_BUFFER, sizeof(data) * count, data, GL_STATIC_DRAW);
    //put vbo into the vao: num of attribute list, length of vertex, type of data, distance between vertices, offset from start
    glVertexAttribPointer(attNum, 3, GL_FLOAT, GL_FALSE, 0, nullptr);
    //unbind the vbo, 0 unbinds the current one
    glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void Loader::cleanUp() {
    //delete all vaos
    for(auto vao : _vaos) {
        glDeleteVertexArrays(1, &vao);
    }

    //delete all vbos
    for(auto vbo : _vbos) {
        glDeleteBuffers(1, &vbo);
    }
}



