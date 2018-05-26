#include <models/textured_model.h>
#include <entities/entity.h>
#include <utilities/maths.h>
#include "terrain_renderer.h"

Shader TerrainRenderer::_shader;

void TerrainRenderer::initialise(const Shader &shader, const glm::mat4 &projMat) {
    _shader = shader;
    _shader.use();
    _shader.setMatrix("projectionMatrix", projMat);
    _shader.setInt("backgroundTexture", 0);
    _shader.setInt("rTexture", 1);
    _shader.setInt("gTexture", 2);
    _shader.setInt("bTexture", 3);
    _shader.setInt("blendMap", 4);
    _shader.stop();
}

void TerrainRenderer::render(const std::vector<Terrain> &terrains) {
    for(const auto &terrain : terrains) {
        prepareTerrain(terrain);
        prepareInstance(terrain);
        glDrawElements(GL_TRIANGLES, terrain.get_model().get_vertexCount(), GL_UNSIGNED_INT, nullptr);
        unbindTexturedModel();
    }
}

void TerrainRenderer::prepareTerrain(const Terrain &terrain) {
    auto rawModel = terrain.get_model();
    //bind the texturedModel's vao
    glBindVertexArray(rawModel.get_vaoID());
    //activate the attribute list
    glEnableVertexAttribArray(0); //indices
    glEnableVertexAttribArray(1); //texture coordinates
    glEnableVertexAttribArray(2); //normals

    //set the lighting uniforms in the shaders
    bindTextures(terrain);
    _shader.setFloat("shineDamper", 1.f);
    _shader.setFloat("reflectivity", 0.f);
}

void TerrainRenderer::bindTextures(const Terrain &terrain) {
    auto pack = terrain.get_texturePack();
    //set the active texture
    glActiveTexture(GL_TEXTURE0);
    //bind the model's texture
    glBindTexture(GL_TEXTURE_2D, pack.get_backgroundTexture().ID);
    //set the active texture
    glActiveTexture(GL_TEXTURE1);
    //bind the model's texture
    glBindTexture(GL_TEXTURE_2D, pack.get_rTexture().ID);
    //set the active texture
    glActiveTexture(GL_TEXTURE2);
    //bind the model's texture
    glBindTexture(GL_TEXTURE_2D, pack.get_gTexture().ID);
    //set the active texture
    glActiveTexture(GL_TEXTURE3);
    //bind the model's texture
    glBindTexture(GL_TEXTURE_2D, pack.get_bTexture().ID);
    //set the active texture
    glActiveTexture(GL_TEXTURE4);
    //bind the model's texture
    glBindTexture(GL_TEXTURE_2D, terrain.get_blendMap().ID);
    //enable textures
    //glEnable(GL_TEXTURE_2D);
}

void TerrainRenderer::unbindTexturedModel() {
    //disable the attribute lists
    glDisableVertexAttribArray(0);
    glDisableVertexAttribArray(1);
    glDisableVertexAttribArray(2);

    //unbind the vao
    glBindVertexArray(0);
}

void TerrainRenderer::prepareInstance(const Terrain &terrain) {
    //calculate the transformation matrix using the model's position, rotation and scale
    glm::mat4 transformationMat = Maths::createTransformationMatrix(glm::vec3(terrain.get_x(), 0.f, terrain.get_z()), glm::vec3(0, 0, 0), 1.f);
    _shader.setMatrix("transformationMatrix", transformationMat);
}



