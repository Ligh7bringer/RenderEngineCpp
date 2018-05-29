#ifndef RENDERENGINE_IMAGE_H
#define RENDERENGINE_IMAGE_H

#include <stb_image.h>
#include "../../lib/glm/glm/vec4.hpp"
#include <glad/glad.h>

#include <string>
#include <stdexcept>

class Image {
public:
    explicit Image(const std::string& name)  {
		auto path = name;
		int width, height, nrChannels;
		//load the texture with stbi
		unsigned char* data = stbi_load(path.c_str(), &width, &height, &nrChannels, STBI_rgb_alpha);
		unsigned int texture;
		//generate a texture and store its id
		glGenTextures(1, &texture);
		glBindTexture(GL_TEXTURE_2D, texture);
		// set texture filtering parameters
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_LOD_BIAS, -1.f);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
		//if the image was loaded successfully
		if (data) {
			//NOTE: GL_RGBA is the correct channel for images with an alpha channel
			glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
			//so this line generates lower resolutions of the texture
			glGenerateMipmap(GL_TEXTURE_2D);
		}
		else {
			throw std::runtime_error("Texture " + path + " couldn't be loaded!");
		}

		_data = data;
		_id = texture;
		_channels = nrChannels;
		_width = width;
		_height = height;		
	}

	int getHeight() const {
		return _height;
	}

	int getWidth() const {
		return _width;
	}

	unsigned int getID() const {
		return _id;
	}

	unsigned char *getData() const {
		return _data;
	}

	//returns RGBA value of pixel at i, j or should do
    glm::vec4 getRGB(unsigned int i, unsigned int j) const {
        unsigned bytePerPixel = _channels;
        unsigned char* pixelOffset = _data + (i + _height * j) * bytePerPixel;
        unsigned char r = pixelOffset[0];
        unsigned char g = pixelOffset[1];
        unsigned char b = pixelOffset[2];
        unsigned char a = _channels >= 4 ? pixelOffset[3] : 0xff;
        return glm::vec4 { r, g, b, a };
    }

    //i do not have a clue what this does
    std::int32_t getRGBSum(int x, int y) const {
            int addr = (y * _width + x) * _channels;
            std::int32_t r = _data[addr];
            std::int32_t g = _data[addr + 1];
            std::int32_t b = _data[addr + 2];
            return (r << 16) + (g << 8) + b; //magic
    }

    virtual ~Image() {
		if (_data != nullptr) {
			delete[] _data;
		}
	}

private:
	const std::string RES_DIR = "res/textures/";
	unsigned int _id;
	unsigned char* _data;
	int _channels;
	int _width;
	int _height;
};


#endif //RENDERENGINE_IMAGE_H