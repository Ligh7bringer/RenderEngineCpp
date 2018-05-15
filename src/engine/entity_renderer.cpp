#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <entities/entity.h>
#include <shaders/shader.h>
#include <utilities/maths.h>
#include <Log.h>
#include "entity_renderer.h"
#include "window_manager.h"
#include "master_renderer.h"

Shader Renderer::_shader;

//creates the projection matrix and passes it to the shaders
void Renderer::initialise(Shader &shader, const glm::mat4 &projMat) {
    _shader = shader;
    _shader.use();
    //set the uniform, setting it once is enough as it shouldn't change
    _shader.setMatrix("projectionMatrix", projMat);
    _shader.stop();
}

void Renderer::render(const std::map<TexturedModel, std::vector<Entity>> &entities) {
    for(const auto &model : entities) {
        prepareTexturedModel(model.first);
        auto batch = model.second;

        for(const auto &entity : batch) {
            prepareInstance(entity);
            //render
            glDrawElements(GL_TRIANGLES, model.first.getModel().get_vertexCount(), GL_UNSIGNED_INT, nullptr);
        }

        unbindTexturedModel();
    }
}

void Renderer::prepareTexturedModel(const TexturedModel &model) {
    auto rawModel = model.getModel();
    //bind the texturedModel's vao
    glBindVertexArray(rawModel.get_vaoID());
    //activate the attribute list
    glEnableVertexAttribArray(0); //indices
    glEnableVertexAttribArray(1); //texture coordinates
    glEnableVertexAttribArray(2); //normals

    //set the lighting uniforms in the shaders
    auto tex = model.getTexture();
    if(tex.hasTransparency()) {
        MasterRenderer::disableCulling();
    }
    _shader.setFloat("useFakeLighting", tex.getFakeLighting());
    _shader.setFloat("shineDamper", tex.getShineDamper());
    _shader.setFloat("reflectivity", tex.getReflectivity());

    //set the active texture
    glActiveTexture(GL_TEXTURE0);
    //bind the model's texture
    glBindTexture(GL_TEXTURE_2D, model.getTexture().getID());
    //enable textures
    glEnable(GL_TEXTURE_2D);
}

void Renderer::unbindTexturedModel() {
    MasterRenderer::enableCulling();
    //disable the attribute lists
    glDisableVertexAttribArray(0);
    glDisableVertexAttribArray(1);
    glDisableVertexAttribArray(2);

    //unbind the vao
    glBindVertexArray(0);
}

void Renderer::prepareInstance(const Entity &entity) {
    //calculate the transformation matrix using the model's position, rotation and scale
    glm::mat4 transformationMat = Maths::createTransformationMatrix(entity.getPosition(), entity.getRotation(), entity.getScale());
    _shader.setMatrix("transformationMatrix", transformationMat);
}


