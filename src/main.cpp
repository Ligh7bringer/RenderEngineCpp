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
#include <entities/player.h>

structlog LOGCFG = {};

float randCoord(int min = -800, int max = 800) {
    return min + static_cast <float> (rand()) /( static_cast <float> (RAND_MAX/(max-min)));
}

int main() {
    //set up logging:
    //display logging level
    LOGCFG.headers = true;
    //min logging level
    LOGCFG.level = DEBUG;

    //create a window
    WindowManager::createWindow(glm::vec2(1280, 720), "Render Engine");

    TexturedModel tree = TexturedModel(OBJLoader::loadModel("tree"), ModelTexture(Loader::loadTexture("tree")));
    TexturedModel grass = TexturedModel(OBJLoader::loadModel("grassModel"), ModelTexture(Loader::loadTexture("grassTexture"), true, true));
    TexturedModel fern = TexturedModel(OBJLoader::loadModel("fern"), ModelTexture(Loader::loadTexture("fern"), true, true));
    TexturedModel playerModel = TexturedModel(OBJLoader::loadModel("player"), ModelTexture(Loader::loadTexture("playerTexture")));

    std::vector<Entity> entities;
    for(int i = 0; i < 1; ++i) {
        auto ent = Entity(tree, glm::vec3(randCoord(), 0.f, randCoord()), glm::vec3(0.f, 0.f, 0.f), 3.f);
        auto ent2 = Entity(grass, glm::vec3(randCoord(), 0.f, randCoord()), glm::vec3(0.f, 0.f, 0.f), 1.f);
        auto ent3 = Entity(fern, glm::vec3(randCoord(), 0.f, randCoord()), glm::vec3(0.f, 0.f, 0.f), 0.5f);

        entities.push_back(ent);
        entities.push_back(ent2);
        entities.push_back(ent3);
    }

    Player player = Player(playerModel, glm::vec3(400.f, 0.f, 400.f), glm::vec3(0.f, 0.f, 0.f), 0.4f);
    Camera cam = Camera(player);

    //terrains ----------------------------------------------------------------
    /* textures */
    TerrainTexture bgTex = TerrainTexture(Loader::loadTexture("grass"));
    TerrainTexture rTex = TerrainTexture(Loader::loadTexture("mud"));
    TerrainTexture gTex = TerrainTexture(Loader::loadTexture("grassFlowers"));
    TerrainTexture bTex = TerrainTexture(Loader::loadTexture("path"));
    TerrainTexture blendMap = TerrainTexture(Loader::loadTexture("blendMap2"));
    TerrainTexturePack pack = TerrainTexturePack(bgTex, rTex, gTex, bTex);
    /*---------------------------------------------------*/
    Terrain terrain = Terrain(0, -1, pack, blendMap, "heightmap2");
    //Terrain terrain2 = Terrain(1, -1, pack, blendMap, "heightmap");
    //-------------------------------------------------------------------------

    Light light = Light(glm::vec3(2000.f, 2000.f, -1000.f), glm::vec3(1.f, 1.f, 1.f));

    MasterRenderer::initialise();

    // Rendering Loop
    while (WindowManager::shouldClose() == 0) {
        //handle keyboard input
        cam.move();
        player.move();

        for(const auto& cube : entities) {
            //process entities
            MasterRenderer::processEntity(cube);
        }

        MasterRenderer::processEntity(player);

        MasterRenderer::processTerrain(terrain);
        //MasterRenderer::processTerrain(terrain2);

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
