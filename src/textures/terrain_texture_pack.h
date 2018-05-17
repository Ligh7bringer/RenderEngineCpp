#ifndef RENDERENGINE_TERRAIN_TEXTURE_PACK_H
#define RENDERENGINE_TERRAIN_TEXTURE_PACK_H

#include "terrain_texture.h"

class TerrainTexturePack {
public:
    TerrainTexturePack(const TerrainTexture &backgroundTexture, const TerrainTexture &rTexture,
                       const TerrainTexture &gTexture, const TerrainTexture &bTexture) :
                                                        _backgroundTexture(backgroundTexture), _rTexture(rTexture),
                                                        _gTexture(gTexture), _bTexture(bTexture) {}


    // -- getters -----------------------
    const TerrainTexture &get_backgroundTexture() const {
        return _backgroundTexture;
    }

    const TerrainTexture &get_rTexture() const {
        return _rTexture;
    }

    const TerrainTexture &get_gTexture() const {
        return _gTexture;
    }

    const TerrainTexture &get_bTexture() const {
        return _bTexture;
    }

private:
    TerrainTexture _backgroundTexture;
    TerrainTexture _rTexture;
    TerrainTexture _gTexture;
    TerrainTexture _bTexture;
};

#endif //RENDERENGINE_TERRAIN_TEXTURE_PACK_H
