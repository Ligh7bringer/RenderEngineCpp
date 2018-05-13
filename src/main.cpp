// Local Headers
#include "engine/display_manager.h"
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
#include <engine/maths.h>

structlog LOGCFG = {};

int main(int argc, char * argv[]) {
    //set up logging:
    //display logging level
    LOGCFG.headers = true;
    //min logging level
    LOGCFG.level = DEBUG;

    //create a display manager
    DisplayManager displayManager = DisplayManager();
    //create window
    displayManager.create_display();

    Loader loader = Loader();
    Renderer renderer = Renderer();

    std::vector<float> vertices = {
            -0.5f, 0.5f, 0.f, //v0
            -0.5f, -0.5f, 0.f, //v1
            0.5f, -0.5f, 0.f, //v2
            0.5f, 0.5f, 0.f, //v3
    };

    std::vector<unsigned int> indices {
        0, 1, 3, 3, 1, 2
    };

    std::vector<float> texCoords {
        0, 0,
        0, 1,
        1, 1,
        1, 0
    };

    RawModel model = loader.loadToVAO(vertices, indices, texCoords);
    ModelTexture texture = ModelTexture(loader.loadTexture("plane"));
    TexturedModel texturedModel(model, texture);

    Shader shader("res/shaders/basic.vert", "res/shaders/basic.frag");
    //shader.setMatrix("transformationMatrix", glm::mat4());

    // Rendering Loop
    while (displayManager.should_close() == 0) {
        renderer.prepare();

        shader.use();
        renderer.render(texturedModel);
        shader.stop();

        displayManager.update_display();
    }

    loader.cleanUp();
    shader.cleanUp();
    displayManager.close_display();

    return EXIT_SUCCESS;
}
