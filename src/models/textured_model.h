#ifndef RENDERENGINE_TEXTURED_MODEL_H
#define RENDERENGINE_TEXTURED_MODEL_H


#include <textures/model_texture.h>
#include "raw_model.h"

class TexturedModel {
public:
    explicit TexturedModel(const RawModel &model, const ModelTexture &tex) : _rawModel(model), _texture(tex) {}

    const RawModel &getModel() const {
        return _rawModel;
    }

    const ModelTexture &getTexture() const {
        return _texture;
    }

private:
    RawModel _rawModel;
    ModelTexture _texture;
};


#endif //RENDERENGINE_TEXTURED_MODEL_H
