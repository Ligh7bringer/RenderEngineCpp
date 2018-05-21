#ifndef RENDERENGINE_MODEL_TEXTURE_H
#define RENDERENGINE_MODEL_TEXTURE_H


class ModelTexture {
public:
    //very simple class, used to store some data about a texture
    explicit ModelTexture(unsigned int id, bool transparent=false, bool fakeLighting=false, int numOfRows=1) : _ID(id),
           _shineDamper(1.0f), _reflectivity(0.f),
            _hasTransparency(transparent), _fakeLighting(fakeLighting),
            _numOfRows(numOfRows) {}

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

    int getNumOfRows() const {
        return _numOfRows;
    }

    void setNumOfRows(int _numOfRows) {
        ModelTexture::_numOfRows = _numOfRows;
    }

private:
    unsigned int _ID;
    float _shineDamper;
    float _reflectivity;
    bool _hasTransparency;
    bool _fakeLighting;
    int _numOfRows;
};


#endif //RENDERENGINE_MODEL_TEXTURE_H
