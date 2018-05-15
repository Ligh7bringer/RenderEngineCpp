#ifndef RENDERENGINE_MODEL_TEXTURE_H
#define RENDERENGINE_MODEL_TEXTURE_H


class ModelTexture {
public:
    //very simple class, everything needed is the texture id
    explicit ModelTexture(unsigned int id) : _ID(id), _shineDamper(1.0f), _reflectivity(0.f) {}

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

private:
    unsigned int _ID;
    float _shineDamper;
    float _reflectivity;
};


#endif //RENDERENGINE_MODEL_TEXTURE_H
