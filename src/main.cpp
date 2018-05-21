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
#include <entities/player.h>
#include <engine/gui_renderer.h>

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

    auto rockTex = ModelTexture(Loader::loadTexture("rock2"));
    rockTex.setShineDamper(1.f);
    rockTex.setReflectivity(0.3f);

    //models
    TexturedModel tree = TexturedModel(OBJLoader::LOAD("pine"), ModelTexture(Loader::loadTexture("pine")));
    TexturedModel rock = TexturedModel(OBJLoader::LOAD("rock2"), rockTex);
    TexturedModel fern = TexturedModel(OBJLoader::LOAD("fern"), ModelTexture(Loader::loadTexture("fern"), true, true, 2));
    TexturedModel grass = TexturedModel(OBJLoader::LOAD("grassModel"), ModelTexture(Loader::loadTexture("grassAtlas"), true, true, 4));
    TexturedModel playerModel = TexturedModel(OBJLoader::LOAD("player"), ModelTexture(Loader::loadTexture("playerTexture")));
    //--

    Player player = Player(playerModel, glm::vec3(0.f, 80.f, 0.f), glm::vec3(0.f, 0.f, 0.f), 0.4f);
    Camera cam = Camera(player);

    //terrains ----------------------------------------------------------------
    /* textures */
    TerrainTexture bgTex = TerrainTexture(Loader::loadTexture("grass"));
    TerrainTexture rTex = TerrainTexture(Loader::loadTexture("mud"));
    TerrainTexture gTex = TerrainTexture(Loader::loadTexture("grassFlowers"));
    TerrainTexture bTex = TerrainTexture(Loader::loadTexture("path"));
    TerrainTexture blendMap = TerrainTexture(Loader::loadTexture("blendMap"));
    TerrainTexturePack pack = TerrainTexturePack(bgTex, rTex, gTex, bTex);
    /*---------------------------------------------------*/
    Terrain terrain = Terrain(0, -1, pack, blendMap, "heightmap");
    //-------------------------------------------------------------------------

    std::vector<Entity> entities;
    for(int i = 0; i < 60; ++i) {
        auto x = randCoord(0, 800);
        auto z = randCoord(0, 800);
        auto y = terrain.getHeightOfTerrain(x, z);
        auto ent = Entity(tree, glm::vec3(x, y, z), glm::vec3(0.f, randCoord(0, 270), 0.f), 3.f);
        x = randCoord(0, 800);
        z = randCoord(0, 800);
        y = terrain.getHeightOfTerrain(x, z);
        auto ent2 = Entity(rock, glm::vec3(x, y, z), glm::vec3(0.f, 0.f, 0.f), 3.f);
        x = randCoord(0, 800);
        z = randCoord(0, 800);
        y = terrain.getHeightOfTerrain(x, z);
        auto ent3 = Entity(fern, rand() % 4, glm::vec3(x, y, z), glm::vec3(0.f, 0.f, 0.f), 0.5f);
        x = randCoord(0, 800);
        z = randCoord(0, 800);
        y = terrain.getHeightOfTerrain(x, z);
        auto ent4 = Entity(grass, rand() % 9, glm::vec3(x, y, z), glm::vec3(0.f, 0.f, 0.f), 3.f);

        entities.push_back(ent);
        entities.push_back(ent2);
        entities.push_back(ent3);
        entities.push_back(ent4);
    }

    Light light = Light(glm::vec3(2000.f, 2000.f, -1000.f), glm::vec3(1.f, 1.f, 1.f));

    MasterRenderer::initialise();
    GuiRenderer::initialise();

    std::vector<GuiTexture> guis;
    GuiTexture gui = GuiTexture(Loader::loadTexture("health"), glm::vec2(-0.85f, 0.9f), glm::vec2(0.15f, 0.25f));
    guis.push_back(gui);

    // Rendering Loop
    while (WindowManager::shouldClose() == 0) {
        //handle keyboard input
        cam.move();
        player.move(terrain);

        for(const auto& cube : entities) {
            //process entities
            MasterRenderer::processEntity(cube);
        }

        MasterRenderer::processEntity(player);
        MasterRenderer::processTerrain(terrain);

        //render entities
        MasterRenderer::render(light, cam);
        GuiRenderer::render(guis);

        //update window
        WindowManager::updateWindow();
        //show fps
        WindowManager::showUPS();
    }

    MasterRenderer::cleanUp();
    GuiRenderer::cleanUp();
    Loader::cleanUp();
    WindowManager::closeWindow();

    return EXIT_SUCCESS;
}
