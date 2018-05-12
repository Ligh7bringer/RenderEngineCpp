#include <glad/glad.h>
#include "renderer.h"

void Renderer::prepare() {
    //set clear colour
    glClearColor(0.0f, 0.5f, 0.5f, 1.0f);
    //clear colour buffer
    glClear(GL_COLOR_BUFFER_BIT);
}

void Renderer::render(RawModel model) {
    //bind the model's vao
    glBindVertexArray(model.get_vaoID());
    //activate the attribute list, 0 is the one used
    glEnableVertexAttribArray(0);
    //render
    glDrawArrays(GL_TRIANGLES, 0, model.get_vertexCount());
    //disable the attribute list
    glDisableVertexAttribArray(0);
    //unbind the vao
    glBindVertexArray(0);
}
