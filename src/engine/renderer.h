#ifndef RENDERENGINE_RENDERER_H
#define RENDERENGINE_RENDERER_H

#include "models/raw_model.h"

class Renderer {
private:

public:
    void prepare();
    void render(RawModel model);
};


#endif //RENDERENGINE_RENDERER_H
