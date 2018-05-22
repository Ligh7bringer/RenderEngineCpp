#include <loader.h>
#include "gui_renderer.h"

#include <glad/glad.h>
#include <Log.h>
#include <utilities/maths.h>

RawModel GuiRenderer::_model;
Shader GuiRenderer::_shader;

void GuiRenderer::initialise() {
    _shader = Shader("res/shaders/gui.vert", "res/shaders/gui.frag");
    std::vector<float> positions = {
            -1, 1, -1, -1, 1, 1, 1, -1
    };
    _model = Loader::loadToVao(positions, 2);
}

void GuiRenderer::render(std::vector<GuiTexture> guis) {
    _shader.use();
    glBindVertexArray(_model.get_vaoID());
    glEnableVertexAttribArray(0);
    glEnable(GL_BLEND); //make it transparent!
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA); //set blend function
    glDisable(GL_DEPTH_TEST); //make sure guis can overlap and still be visible

    for(const auto &gui : guis) {
        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, gui.getID());
        auto transformMatrix = Maths::createTransformationMatrix(gui.getPosition(), gui.getScale());
        _shader.setMatrix("transformationMatrix", transformMatrix);
        glDrawArrays(GL_TRIANGLE_STRIP, 0, _model.get_vertexCount());
    }

    glEnable(GL_DEPTH_TEST);
    glDisable(GL_BLEND);
    glDisableVertexAttribArray(0);
    glBindVertexArray(0);
    _shader.stop();
}

void GuiRenderer::cleanUp() {
    _shader.cleanUp();
}


