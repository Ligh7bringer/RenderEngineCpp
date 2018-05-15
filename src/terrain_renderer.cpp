#include <models/textured_model.h>
#include <entities/entity.h>
#include <utilities/maths.h>
#include "terrain_renderer.h"

Shader TerrainRenderer::_shader;

void TerrainRenderer::initialise(const Shader &shader, const glm::mat4 &projMat) {
    _shader = shader;
    _shader.use();
    _shader.setMatrix("projectionMatrix", projMat);
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
    auto tex = terrain.get_texture();
    _shader.setFloat("shineDamper", tex.getShineDamper());
    _shader.setFloat("reflectivity", tex.getReflectivity());

    //set the active texture
    glActiveTexture(GL_TEXTURE0);
    //bind the model's texture
    glBindTexture(GL_TEXTURE_2D, tex.getID());
    //enable textures
    glEnable(GL_TEXTURE_2D);
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
    glm::mat4 transformationMat = Maths::createTransformationMatrix(glm::vec3(terrain.get_x(), 0, terrain.get_z()), glm::vec3(0, 0, 0), 1.f);
    _shader.setMatrix("transformationMatrix", transformationMat);
}