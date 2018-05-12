#ifndef RENDERENGINE_RAW_MODEL_H
#define RENDERENGINE_RAW_MODEL_H


class RawModel {
private:
    unsigned int _vaoID;
    unsigned int _vertexCount;

public:
    RawModel() = delete;

    //set the vao id and vertex count
    explicit RawModel(unsigned int id, unsigned int count) {
        _vaoID = id;
        _vertexCount = count;
    }

    unsigned int get_vaoID() const { return _vaoID; }
    int get_vertexCount() const { return _vertexCount; }

};


#endif //RENDERENGINE_RAW_MODEL_H
