#include <glad/glad.h>
#include <glm/gtc/matrix_transform.hpp>
#include <GLFW/glfw3.h>

#include <entities/entity.h>
#include <shaders/shader.h>
#include <utilities/maths.h>
#include <Log.h>
#include "renderer.h"
#include "window_manager.h"

glm::mat4 Renderer::_projectionMatrix;
Shader Renderer::_shader;

//some constants needed for the projection matrix
const float FOV = 70.f;
const float NEAR_PLANE = 0.1f;
const float FAR_PLANE = 1000.f;

//creates the projection matrix and passes it to the shaders
void Renderer::initialise(Shader &shader) {
    _shader = shader;
    //enable face culling so that not visible faces are not rendered
    glEnable(GL_CULL_FACE);
    glCullFace(GL_BACK);
    createProjectionMatrix();
    _shader.use();
    //set the uniform, setting it once is enough as it shouldn't change
    _shader.setMatrix("projectionMatrix", _projectionMatrix);
    _shader.stop();
}

void Renderer::prepare() {
    //enable depth test so that vertices can be drawn in the correct order
    glEnable(GL_DEPTH_TEST);
    //clear colour buffer and depth buffer
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    //set background colour
    glClearColor(0.0f, 0.5f, 0.5f, 1.0f);
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

//creates the projection matrix
void Renderer::createProjectionMatrix() {
    //get window size
    auto winSize = WindowManager::getWindowSize();
    //calculate the matrix using the very convenient glm method
    _projectionMatrix = glm::perspectiveFov(glm::radians(FOV), winSize.x, winSize.y, NEAR_PLANE, FAR_PLANE);
}
