#ifndef RENDERENGINE_WATER_TILE_H
#define RENDERENGINE_WATER_TILE_H


class WaterTile {
public:
    WaterTile(float centerX, float centerZ, float height) :
            _x(centerX), _z(centerZ), _height(height) {}

    float getX() const {
        return _x;
    }

    float getZ() const {
        return _z;
    }

    float getHeight() const {
        return _height;
    }

    float getTileSize() const {
        return TILE_SIZE;
    }

private:
    const float TILE_SIZE = 125.f;

    float _x, _z;
    float _height;

};


#endif //RENDERENGINE_WATER_TILE_H
