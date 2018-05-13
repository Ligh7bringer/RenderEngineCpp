#ifndef RENDERENGINE_MODEL_TEXTURE_H
#define RENDERENGINE_MODEL_TEXTURE_H


class ModelTexture {
public:
    explicit ModelTexture(unsigned int id) {
        _ID = id;
    }

    unsigned int getID() const { return _ID; }

private:
    unsigned int _ID;
};


#endif //RENDERENGINE_MODEL_TEXTURE_H
