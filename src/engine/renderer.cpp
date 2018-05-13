#include <glad/glad.h>
#include <glm/gtc/matrix_transform.hpp>
#include <entities/entity.h>
#include <shaders/shader.h>
#include <utilities/maths.h>
#include <GLFW/glfw3.h>
#include "renderer.h"
#include "window_manager.h"

//some constants needed for the projection matrix
const float FOV = 70.f;
const float NEAR_PLANE = 0.1f;
const float FAR_PLANE = 1000.f;

void Renderer::prepare() {
    //enable depth test so that vertices can be drawn in the correct order
    glEnable(GL_DEPTH_TEST);
    //clear colour buffer and depth buffer
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    //set background colour
    glClearColor(0.0f, 0.5f, 0.5f, 1.0f);
}

//renders an entity
void Renderer::render(const Entity &entity, const Shader &shader) {
    //get the models from the entity
    TexturedModel model = entity.getModel();
    RawModel rawModel = model.getModel();
    //bind the texturedModel's vao
    glBindVertexArray(rawModel.get_vaoID());
    //activate the attribute list, 0 is the one used
    glEnableVertexAttribArray(0);
    glEnableVertexAttribArray(1);

    //calculate the transformation matrix using the model's position, rotation and scale
    glm::mat4 transformationMat = Maths::createTransformationMatrix(entity.getPosition(), entity.getRotation(), entity.getScale());
    shader.setMatrix("transformationMatrix", transformationMat);

    //set the active texture
    glActiveTexture(GL_TEXTURE0);
    //bind the model's texture
    glBindTexture(GL_TEXTURE_2D, model.getTexture().getID());
    //enable textures
    glEnable(GL_TEXTURE_2D);

    //render
    glDrawElements(GL_TRIANGLES, rawModel.get_vertexCount(), GL_UNSIGNED_INT, nullptr);
    //disable the attribute lists
    glDisableVertexAttribArray(0);
    glDisableVertexAttribArray(1);
    //unbind the vao
    glBindVertexArray(0);
}

//creates the projection matrix
void Renderer::createProjectionMatrix() {
    //get window size
    auto winSize = DisplayManager::getWindowSize();
    //calculate the matrix using the very convenient glm method
    _projectionMatrix = glm::perspectiveFov(glm::radians(FOV), winSize.x, winSize.y, NEAR_PLANE, FAR_PLANE);
}

//constructor
Renderer::Renderer(Shader &shader) {
    createProjectionMatrix();
    shader.use();
    //set the uniform, setting it once is enough as it shouldn't change
    shader.setMatrix("projectionMatrix", _projectionMatrix);
    shader.stop();
}
