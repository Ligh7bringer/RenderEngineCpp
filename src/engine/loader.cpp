#include <glad/glad.h>
#include <Log.h>
#include "loader.h"

#define STB_IMAGE_IMPLEMENTATION
#include <stb_image.h>

const std::string TEX_DIR = "res/textures/";

//creates a raw model with the passed vertices
RawModel
Loader::loadToVAO(vector<float> &positions, vector<unsigned int> &indices, vector<float> &texCoords) {
    //create a vertex array
    unsigned int vaoID = createVAO();
    bindIndicesBuffer(indices);
    //store the data, starting from index 0
    storeData(0, positions, 3);
    storeData(1, texCoords, 2);
    unbindVAO();

    //create and return the model
    return RawModel(vaoID, static_cast<int>(indices.size()));
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

void Loader::storeData(unsigned int attNum, vector<float> &data, unsigned int coordSize) {
    //create a vbo
    auto vboID = createVBO();
    //store it for later
    _vbos.push_back(vboID);
    //bind it so it can be used
    glBindBuffer(GL_ARRAY_BUFFER, vboID);
    //store data in the vbo: type of buffer, size, actual data, draw type
    //NOTE: &data.front() returns a pointer to the beginning of the vector, so it's like passing a float array which is exactly what openGL is expecting
    glBufferData(GL_ARRAY_BUFFER, sizeof(float) * data.size(), &data.front(), GL_STATIC_DRAW);
    //put vbo into the vao: num of attribute list, length of vertex, type of data, distance between vertices, offset from start
    glVertexAttribPointer(attNum, coordSize, GL_FLOAT, GL_FALSE, 0, nullptr);
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

    for(auto tex : _textures) {
        glDeleteTextures(1, &tex);
    }
}

void Loader::bindIndicesBuffer(vector<unsigned int> &indices) {
    unsigned int vboID;
    glGenBuffers(1, &vboID);
    _vbos.push_back(vboID);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, vboID);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(unsigned int) * indices.size(), &indices.front(), GL_STATIC_DRAW);
}

unsigned int Loader::loadTexture(const std::string &fileName) {
    int width, height, nrChannels;
    string loc = TEX_DIR + fileName + ".png";
    unsigned char* data = stbi_load(loc.c_str(), &width, &height, &nrChannels, 4);
    unsigned int texture;
    glGenTextures(1, &texture);
    glBindTexture(GL_TEXTURE_2D, texture);

    if(data) {
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
        glGenerateMipmap(GL_TEXTURE_2D);

    } else {
        LOG(ERROR) << "Texture " << loc << " couldn't be loaded!";
    }

    stbi_image_free(data);

    return texture;
}



