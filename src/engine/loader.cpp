#include <Log.h>
#include "loader.h"

#define STB_IMAGE_IMPLEMENTATION
#include <stb_image.h>
#include <glm/glm.hpp>

#include <textures/image.h>


const std::string TEX_DIR = "res/textures/";

std::vector<unsigned int> Loader::_vaos;
std::vector<unsigned int> Loader::_vbos;
std::vector<unsigned int> Loader::_textures;

//creates a raw model with the passed vertices
RawModel Loader::loadToVAO(std::vector<float> &positions, std::vector<unsigned int> &indices, std::vector<float> &normals,
                  std::vector<float> &texCoords) {
    //create a vertex array
    unsigned int vaoID = createVAO();
    bindIndicesBuffer(indices);
    //store the data, starting from index 0
    storeData(0, 3, positions);
    storeData(1, 2, texCoords);
    storeData(2, 3, normals);
    unbindVAO();

    //create and return the model
    return RawModel(vaoID, static_cast<int>(indices.size()));
}

//overload of method above
RawModel Loader::loadToVao(std::vector<float> &positions, int dimensions) {
    auto vaoID = createVAO();
    storeData(0, dimensions, positions);
    unbindVAO();
    return RawModel(vaoID, static_cast<unsigned int>(positions.size() / dimensions));
}

RawModel Loader::loadToVao(std::vector<glm::vec3> &positions, std::vector<unsigned int> &indices,
                           std::vector<glm::vec3> &normals, std::vector<glm::vec2> &texCoords) {

    //create a vertex array
    unsigned int vaoID = createVAO();
    bindIndicesBuffer(indices);
    //store the data, starting from index 0
    storeData(0, 3, positions);
    storeData(1, 2, texCoords);
    storeData(2, 3, normals);
    unbindVAO();

    //create and return the model
    return RawModel(vaoID, static_cast<int>(indices.size()));
}

//does the same thing as the method above, however vectors of glm vectors can be used instead of floats (used for model loading)
RawModel Loader::loadToVao(std::vector<glm::vec3> &positions, std::vector<unsigned int> &indices,
                           std::vector<glm::vec3> &normals, std::vector<glm::vec2> &texCoords,
                           std::vector<glm::vec3> &tangents) {

    //create a vertex array
    unsigned int vaoID = createVAO();
    bindIndicesBuffer(indices);
    //store the data, starting from index 0
    storeData(0, 3, positions);
    storeData(1, 2, texCoords);
    storeData(2, 3, normals);
    storeData(3, 3, tangents);
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

//use an EBO for more efficient rendering
void Loader::bindIndicesBuffer(std::vector<unsigned int> &indices) {
    unsigned int vboID;
    //create buffer
    glGenBuffers(1, &vboID);
    //store it
    _vbos.push_back(vboID);
    //bind it so it can be used
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, vboID);
    //NOTE: &indices.front() returns a pointer to the data stored in the vector, same as before
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(unsigned int) * indices.size(), &indices.front(), GL_STATIC_DRAW);
}

//loads a .PNG texture
unsigned int Loader::loadTexture(const std::string &fileName) {
    int width, height, nrChannels;
    string loc = TEX_DIR + fileName + ".png";
    //load the texture with stbi
    unsigned char* data = stbi_load(loc.c_str(), &width, &height, &nrChannels, STBI_rgb_alpha);
    unsigned int texture;
    //generate a texture and store its id
    glGenTextures(1, &texture);
    glBindTexture(GL_TEXTURE_2D, texture);
    // set texture filtering parameters
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_LOD_BIAS, -1.f);

    //if the image was loaded successfully
    if(data) {
        //NOTE: GL_RGBA is the correct channel for images with an alpha channel
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
        //so this line generates lower resolutions of the texture
        glGenerateMipmap(GL_TEXTURE_2D);
    } else {
        LOG(ERR) << "Texture " << loc << " couldn't be loaded!";
    }

    //free image data as its not needed anymore
    stbi_image_free(data);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

    return texture;
}

unsigned int Loader::loadCubeMap(const std::vector<std::string> &fileNames) {
    //create texture and store its ID
    unsigned int texID;
    glGenTextures(1, &texID);
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_CUBE_MAP, texID);

    //iterate over the file names
    for(GLuint i = 0; i < 6; ++i) {
        //load each image
        Image img = Image("res/textures/skybox/" + fileNames[i] + ".png");
        glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + i, 0, GL_RGBA, img.getWidth(),
                     img.getHeight(), 0, GL_RGBA, GL_UNSIGNED_BYTE, img.getData());
    }

    //set min and mag filters
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);

    _textures.push_back(texID);
    return texID;
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

void Loader::cleanUp() {
    //delete all vaos
    for(auto vao : _vaos) {
        glDeleteVertexArrays(1, &vao);
    }

    //delete all vbos
    for(auto vbo : _vbos) {
        glDeleteBuffers(1, &vbo);
    }

    //delete textures
    for(auto tex : _textures) {
        glDeleteTextures(1, &tex);
    }
}




