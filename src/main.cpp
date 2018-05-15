// Local Headers
#include "engine/window_manager.h"
#include "Log.h"
#include "engine/loader.h"
#include <textures/model_texture.h>
#include <models/textured_model.h>
#include <utilities/maths.h>
#include <engine/obj_loader.h>
#include <entities/light.h>
#include <engine/master_renderer.h>

// System Headers
#include <glad/glad.h>
#include <glm/glm.hpp>
#include <memory>


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
    RawModel model = OBJLoader::loadModel("cube");
    ModelTexture texture = ModelTexture(Loader::loadTexture("minecraft"));
    texture.setShineDamper(10.f);
    texture.setReflectivity(1.f);
    TexturedModel texturedModel(model, texture);
    //Entity entity(texturedModel, glm::vec3(0.f, 0.f, 20.f), glm::vec3(0.f, 0.f, 0.f), 3.f);

    std::vector<std::shared_ptr<Entity>> cubes;
    for(int i = 0; i < 1500; ++i) {
        auto x = -50.f + static_cast <float> (rand()) /( static_cast <float> (RAND_MAX/(50-(-50))));
        auto y = -50.f + static_cast <float> (rand()) /( static_cast <float> (RAND_MAX/(50-(-50))));
        auto z = static_cast <float> (rand()) / (static_cast <float> (RAND_MAX/300));
        auto ent = std::make_shared<Entity>(texturedModel, glm::vec3(x, y, -z), glm::vec3(static_cast<float>(rand() * 180), static_cast<float>(rand() * 180), 0.f), 3.f);
        cubes.push_back(ent);
    }

    Camera cam = Camera();
    Light light = Light(glm::vec3(0.f, 0.f, -20.f), glm::vec3(1.f, 1.f, 1.f));

    MasterRenderer::initialise();

    // Rendering Loop
    while (WindowManager::shouldClose() == 0) {
        //handle keyboard input
        cam.move();

        for(const auto& cube : cubes) {
            //process entities
            MasterRenderer::processEntity(*cube);
        }

        //render entities
        MasterRenderer::render(light, cam);

        //update window
        WindowManager::updateWindow();
        //show fps
        WindowManager::showUPS();
    }

    MasterRenderer::cleanUp();
    Loader::cleanUp();
    WindowManager::closeWindow();

    return EXIT_SUCCESS;
}
