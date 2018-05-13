#include <glad/glad.h>
#include <models/textured_model.h>
#include "renderer.h"

void Renderer::prepare() {
    //set clear colour
    glClearColor(0.0f, 0.5f, 0.5f, 1.0f);
    //clear colour buffer
    glClear(GL_COLOR_BUFFER_BIT);
}

void Renderer::render(const TexturedModel &texturedModel) {
    RawModel model = texturedModel.getModel();
    //bind the texturedModel's vao
    glBindVertexArray(model.get_vaoID());
    //activate the attribute list, 0 is the one used
    glEnableVertexAttribArray(0);
    glEnableVertexAttribArray(1);
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, texturedModel.getTexture().getID());
    glEnable(GL_TEXTURE_2D);

    //render
    glDrawElements(GL_TRIANGLES, model.get_vertexCount(), GL_UNSIGNED_INT, nullptr);
    //disable the attribute list
    glDisableVertexAttribArray(0);
    glDisableVertexAttribArray(1);
    //unbind the vao
    glBindVertexArray(0);
}
