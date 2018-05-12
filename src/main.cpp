// Local Headers
#include "engine/display_manager.h"
#include "Log.h"
#include "engine/loader.h"
#include "engine/renderer.h"
#include "shaders/shader.h"

// System Headers
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>

// Standard Headers
#include <cstdio>
#include <cstdlib>

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

    float vertices[] = {
            -0.5f, 0.5f, 0.f,
            -0.5f, -0.5f, 0.f,
            0.5f, -0.5f, 0.f,
            0.5f, -0.5f, 0.f,
            0.5f, 0.5f, 0.f,
            -0.5f, 0.5f, 0.f
    };

    RawModel model = loader.loadToVAO(vertices, 18);
    Shader shader("res/shaders/basic.vert", "res/shaders/basic.frag");

    // Rendering Loop
    while (displayManager.should_close() == 0) {
        renderer.prepare();

        shader.use();
        renderer.render(model);

        displayManager.update_display();
    }

    loader.cleanUp();
    displayManager.close_display();

    return EXIT_SUCCESS;
}
