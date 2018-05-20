#ifndef RENDERENGINE_IMAGE_H
#define RENDERENGINE_IMAGE_H

#include <stb_image.h>
#include "../../lib/glm/glm/vec4.hpp"

class Image {
public:
    Image(unsigned int id, unsigned char *data, unsigned int channels, unsigned int width, unsigned int height) : data(data),
                                                                                                 channels(channels),
                                                                                                 width(width),
                                                                                                 height(height), id(id) {}

    unsigned int id;
    unsigned char* data;
    int channels;
    int width;
    int height;

    //returns RGBA value of pixel at i, j or should do
    glm::vec4 getRGB(unsigned int i, unsigned int j) const {
        unsigned bytePerPixel = channels;
        unsigned char* pixelOffset = data + (i + height * j) * bytePerPixel;
        unsigned char r = pixelOffset[0];
        unsigned char g = pixelOffset[1];
        unsigned char b = pixelOffset[2];
        unsigned char a = channels >= 4 ? pixelOffset[3] : 0xff;
        return glm::vec4 { r, g, b, a };
    }

    //i do not have a clue what this does
    std::int32_t getRGBSum(int x, int y) const {
            int addr = (y * width + x) * channels;
            std::int32_t r = data[addr];
            std::int32_t g = data[addr + 1];
            std::int32_t b = data[addr + 2];
            return (r << 16) + (g << 8) + b;
    }

    virtual ~Image() {
        stbi_image_free(data);
    }

private:

};


#endif //RENDERENGINE_IMAGE_H
