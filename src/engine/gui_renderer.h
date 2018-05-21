#ifndef RENDERENGINE_GUI_RENDERER_H
#define RENDERENGINE_GUI_RENDERER_H

#include <vector>

#include <models/raw_model.h>
#include <guis/gui_texture.h>
#include <shaders/shader.h>

class GuiRenderer {
public:
    static void initialise();
    static void cleanUp();
    static void render(std::vector<GuiTexture> guis);

private:
    static RawModel _model;
    static Shader _shader;
};


#endif //RENDERENGINE_GUI_RENDERER_H
