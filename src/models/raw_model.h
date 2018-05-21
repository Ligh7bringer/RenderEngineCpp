#ifndef RENDERENGINE_RAW_MODEL_H
#define RENDERENGINE_RAW_MODEL_H


class RawModel {
private:
    unsigned int _vaoID;
    unsigned int _vertexCount;

public:
    RawModel() = default;
    //set the vao id and vertex count
    explicit RawModel(unsigned int id, unsigned int count) {
        _vaoID = id;
        _vertexCount = count;
    }

    //getters
    unsigned int get_vaoID() const { return _vaoID; }
    int get_vertexCount() const { return _vertexCount; }

    void set_vaoID(unsigned int _vaoID) {
        RawModel::_vaoID = _vaoID;
    }

    void set_vertexCount(unsigned int _vertexCount) {
        RawModel::_vertexCount = _vertexCount;
    }

};


#endif //RENDERENGINE_RAW_MODEL_H
