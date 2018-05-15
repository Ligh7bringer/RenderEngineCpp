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
#include <textures/model_texture.h>
#include <models/textured_model.h>
#include <utilities/maths.h>
#include <engine/obj_loader.h>
#include <entities/light.h>

structlog LOGCFG = {};

int main() {
    //set up logging:
    //display logging level
    LOGCFG.headers = true;
    //min logging level
    LOGCFG.level = DEBUG;

    //create a window
    WindowManager::createWindow(glm::vec2(1280, 720), "Render Engine");

    //create an entity
    RawModel model = OBJLoader::loadModel("dragon");
    ModelTexture texture = ModelTexture(Loader::loadTexture("untextured"));
    texture.setShineDamper(10.f);
    texture.setReflectivity(1.f);
    TexturedModel texturedModel(model, texture);
    Entity entity(texturedModel, glm::vec3(0.0f, -2.5f, -25.f), glm::vec3(0.f, 0.f, 0.f), 1.f);
    Light light = Light(glm::vec3(0.f, 0.f, -20.f), glm::vec3(1.f, 1.f, 1.f));

    RawModel rawStall = OBJLoader::loadModel("stall");
    ModelTexture stallTex = ModelTexture(Loader::loadTexture("stallTexture"));
    stallTex.setShineDamper(10.f);
    stallTex.setReflectivity(0.2f);
    TexturedModel texturedStall(rawStall, stallTex);
    Entity stall(texturedStall, glm::vec3(-13.0f, -2.5f, -25.f), glm::vec3(0.f, 0.f, 0.f), 1.f);

    Shader shader("res/shaders/basic.vert", "res/shaders/basic.frag");
    Renderer renderer = Renderer(shader);

    Camera cam = Camera();

    // Rendering Loop
    while (WindowManager::shouldClose() == 0) {
        //rotate the entity
        entity.rotate(0.f, 0.3f, 0);
        stall.rotate(0.f, 0.3f, 0);
        //handle keyboard input
        cam.move();

        //clear buffers
        renderer.prepare();

        shader.use();
        //set lighting uniforms
        shader.setVector3("lightPosition", light.getPosition());
        shader.setVector3("lightColour", light.getColour());
        //set the uniform variable in the shader
        shader.setMatrix("viewMatrix", Maths::createViewMatrix(cam));
        renderer.render(entity, shader);
        renderer.render(stall, shader);
        shader.stop();

        WindowManager::updateWindow();
        WindowManager::showUPS();
    }

    Loader::cleanUp();
    shader.cleanUp();
    WindowManager::closeWindow();

    return EXIT_SUCCESS;
}
