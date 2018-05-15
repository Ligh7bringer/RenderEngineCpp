#ifndef RENDERENGINE_MODEL_TEXTURE_H
#define RENDERENGINE_MODEL_TEXTURE_H


class ModelTexture {
public:
    //very simple class, everything needed is the texture id
    explicit ModelTexture(unsigned int id) : _ID(id), _hasTransparency(false), _fakeLighting(false), _shineDamper(1.0f), _reflectivity(0.f) {}
    ModelTexture(unsigned int id, bool transparent, bool fakeLighting) : _ID(id), _hasTransparency(transparent), _fakeLighting(fakeLighting), _shineDamper(1.f), _reflectivity(0.f) {}

    unsigned int getID() const { return _ID; }

    float getShineDamper() const {
        return _shineDamper;
    }

    void setShineDamper(float _shineDamper) {
        ModelTexture::_shineDamper = _shineDamper;
    }

    float getReflectivity() const {
        return _reflectivity;
    }

    void setReflectivity(float _reflectivity) {
        ModelTexture::_reflectivity = _reflectivity;
    }

    bool hasTransparency() const {
        return _hasTransparency;
    }

    void setTransparent(bool _hasTransparency) {
        ModelTexture::_hasTransparency = _hasTransparency;
    }

    bool getFakeLighting() const {
        return _fakeLighting;
    }

    void setFakeLighting(bool _fakeLighting) {
        ModelTexture::_fakeLighting = _fakeLighting;
    }

private:
    unsigned int _ID;
    float _shineDamper;
    float _reflectivity;
    bool _hasTransparency;
    bool _fakeLighting;
};


#endif //RENDERENGINE_MODEL_TEXTURE_H
