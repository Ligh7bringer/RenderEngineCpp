#ifndef RENDERENGINE_TEXTURED_MODEL_H
#define RENDERENGINE_TEXTURED_MODEL_H


#include <textures/model_texture.h>
#include "raw_model.h"

class TexturedModel {
public:
    //simple constructor, store the raw model and texture
    explicit TexturedModel(const RawModel &model, const ModelTexture &tex) : _rawModel(model), _texture(tex) {}

    //getters
    const RawModel &getModel() const {
        return _rawModel;
    }

    const ModelTexture &getTexture() const {
        return _texture;
    }

    bool operator <( const TexturedModel &rhs ) const
    {
        return ( _texture.getID() < rhs.getTexture().getID() );
    }

private:
    RawModel _rawModel;
    ModelTexture _texture;
};


#endif //RENDERENGINE_TEXTURED_MODEL_H
