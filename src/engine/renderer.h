#ifndef RENDERENGINE_RENDERER_H
#define RENDERENGINE_RENDERER_H

#include <models/textured_model.h>
#include "models/raw_model.h"

class Renderer {
private:

public:
    void prepare();
    void render(const TexturedModel &texturedModel);
};


#endif //RENDERENGINE_RENDERER_H
