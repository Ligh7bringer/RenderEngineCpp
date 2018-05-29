#include "normal_map_renderer.h"
#include <utilities/maths.h>
#include <utilities/Log.h>
#include "master_renderer.h"

const int MAX_LIGHTS = 4;

NormalMapRenderer::NormalMapRenderer(const glm::mat4 &projMat) : _shader(Shader("res/shaders/normalMap.vert", "res/shaders/normalMap.frag")){
    _shader.use();
    _shader.setMatrix("projectionMatrix", projMat);
    _shader.setInt("modelTexture", 0);
    _shader.setInt("normalMap", 1);
    _shader.stop();
}

void NormalMapRenderer::render(const std::map<TexturedModel, std::vector<Entity>> &entities, const glm::vec4 &clipPlane,
                               const std::vector<Light> &lights, const Camera &camera) {

    _shader.use();
    prepare(clipPlane, lights, camera);

    for(const auto& model : entities) {
        prepareModel(model.first);

        auto batch = model.second;
        for(const auto& entity : batch) {
            prepareInstance(entity);
            glDrawElements(GL_TRIANGLES, model.first.getModel().get_vertexCount(), GL_UNSIGNED_INT, nullptr);
        }

        unbindModel();
    }
    _shader.stop();
}

void NormalMapRenderer::prepareModel(const TexturedModel &model) {
    const auto& rawModel = model.getModel();
    glBindVertexArray(rawModel.get_vaoID());
    glEnableVertexAttribArray(0);
    glEnableVertexAttribArray(1);
    glEnableVertexAttribArray(2);
    glEnableVertexAttribArray(3);

    const auto& tex = model.getTexture();
    //set the lighting uniforms in the shaders
    _shader.setFloat("numberOfRows", tex.getNumOfRows());
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
    //set tex unit
    glActiveTexture(GL_TEXTURE1);
    //bind normal map
    glBindTexture(GL_TEXTURE_2D, model.getTexture().getNormalMap());
}

void NormalMapRenderer::unbindModel() {
    MasterRenderer::enableCulling();
    //disable the attribute lists
    glDisableVertexAttribArray(0);
    glDisableVertexAttribArray(1);
    glDisableVertexAttribArray(2);
    glDisableVertexAttribArray(3);

    //unbind the vao
    glBindVertexArray(0);
}

void NormalMapRenderer::prepareInstance(const Entity &entity) {
    //calculate the transformation matrix using the model's position, rotation and scale
    auto transformationMat = Maths::createTransformationMatrix(entity.getPosition(), entity.getRotation(), entity.getScale());
    _shader.setMatrix("transformationMatrix", transformationMat);
    glm::vec2 offset = {
            entity.getTextureXOffset(),
            entity.getTextureYOffset()
    };
    _shader.setVec2("offset", offset);
}

void NormalMapRenderer::prepare(const glm::vec4 &clipPlane, const std::vector<Light> &lights, const Camera &camera) {
    _shader.setVec4("clipPlane", clipPlane);
    _shader.setVec3("skyColour", MasterRenderer::get_skyColour());

    auto viewMatrix = Maths::createViewMatrix(camera);

    for(int i = 0; i < MAX_LIGHTS; ++i) {
        auto index = i;
        //instead of loading a the last light, make sure the "sun" is loaded!
        if(i == MAX_LIGHTS - 1) {
            //due to the sorting, the sun should be at the end of the list
            index = static_cast<int>(lights.size() - 1);
        }
        _shader.setVec3("lightPositionEyeSpace[" + std::to_string(i) + "]", calculateEyeSpacePos(lights[index], viewMatrix));
        _shader.setVec3("lightColour[" + std::to_string(i) + "]", lights[index].getColour());
        _shader.setVec3("attenuation[" + std::to_string(i) + "]", lights[index].getAttenuation());
    }

    _shader.setMatrix("viewMatrix", viewMatrix);
}

glm::vec3 NormalMapRenderer::calculateEyeSpacePos(const Light &light, const glm::mat4 &viewMatrix) {
    const auto lightPos = light.getPosition();
    glm::vec4 eyeSpacePos = { lightPos.x, lightPos.y, lightPos.z, 1.f };
    eyeSpacePos = viewMatrix * eyeSpacePos;
    return glm::vec3(eyeSpacePos);
}


