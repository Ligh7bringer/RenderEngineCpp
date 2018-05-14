// Local Headers
#include "engine/window_manager.h"
#include "Log.h"
#include "engine/loader.h"
#include "engine/renderer.h"
#include "shaders/shader.h"

// System Headers
#include <glad/glad.h>
#include <glm/glm.hpp>

// Standard Headers
#include <cstdio>
#include <cstdlib>
#include <textures/model_texture.h>
#include <models/textured_model.h>
#include <utilities/maths.h>
#include <engine/obj_loader.h>

structlog LOGCFG = {};

int main(int argc, char * argv[]) {
    //set up logging:
    //display logging level
    LOGCFG.headers = true;
    //min logging level
    LOGCFG.level = DEBUG;

    //create a window
    DisplayManager::createWindow(glm::vec2(1280, 720), "Render Engine");


    //cube vertices, indices and texture coordinates
    std::vector<float> vertices = {
            -0.5f,0.5f,-0.5f,
            -0.5f,-0.5f,-0.5f,
            0.5f,-0.5f,-0.5f,
            0.5f,0.5f,-0.5f,

            -0.5f,0.5f,0.5f,
            -0.5f,-0.5f,0.5f,
            0.5f,-0.5f,0.5f,
            0.5f,0.5f,0.5f,

            0.5f,0.5f,-0.5f,
            0.5f,-0.5f,-0.5f,
            0.5f,-0.5f,0.5f,
            0.5f,0.5f,0.5f,

            -0.5f,0.5f,-0.5f,
            -0.5f,-0.5f,-0.5f,
            -0.5f,-0.5f,0.5f,
            -0.5f,0.5f,0.5f,

            -0.5f,0.5f,0.5f,
            -0.5f,0.5f,-0.5f,
            0.5f,0.5f,-0.5f,
            0.5f,0.5f,0.5f,

            -0.5f,-0.5f,0.5f,
            -0.5f,-0.5f,-0.5f,
            0.5f,-0.5f,-0.5f,
            0.5f,-0.5f,0.5f
    };

    std::vector<unsigned int> indices {
            0,1,3,
            3,1,2,
            4,5,7,
            7,5,6,
            8,9,11,
            11,9,10,
            12,13,15,
            15,13,14,
            16,17,19,
            19,17,18,
            20,21,23,
            23,21,22

    };

    std::vector<float> texCoords {
            0,0,
            0,1,
            1,1,
            1,0,
            0,0,
            0,1,
            1,1,
            1,0,
            0,0,
            0,1,
            1,1,
            1,0,
            0,0,
            0,1,
            1,1,
            1,0,
            0,0,
            0,1,
            1,1,
            1,0,
            0,0,
            0,1,
            1,1,
            1,0
    };

    //create an entity
    RawModel model = OBJLoader::loadModel("dragon");
    ModelTexture texture = ModelTexture(Loader::loadTexture("untextured"));
    TexturedModel texturedModel(model, texture);
    Entity entity(texturedModel, glm::vec3(0.0f, -2.5f, -15.f), glm::vec3(0.f, 0.f, 0.f), 1.f);

    Shader shader("res/shaders/basic.vert", "res/shaders/basic.frag");
    Renderer renderer = Renderer(shader);

    Camera cam = Camera();

    // Rendering Loop
    while (DisplayManager::shouldClose() == 0) {
        //rotate the entity
        entity.rotate(0.f, 0.3f, 0);
        //handle keyboard input
        cam.move();

        //clear buffers
        renderer.prepare();

        shader.use();
        //set the uniform variable in the shader
        shader.setMatrix("viewMatrix", Maths::createViewMatrix(cam));
        renderer.render(entity, shader);
        shader.stop();

        DisplayManager::updateWindow();
        DisplayManager::showUPS();
    }

    Loader::cleanUp();
    shader.cleanUp();
    DisplayManager::closeWindow();

    return EXIT_SUCCESS;
}
