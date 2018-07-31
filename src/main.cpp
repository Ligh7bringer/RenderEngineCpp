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
#include <entities/player.h>
#include <engine/gui_renderer.h>
#include <utilities/mouse_picker.h>
#include <utilities/gl_error.h>

#include <glad/glad.h>
#include <glm/glm.hpp>
#define GLM_ENABLE_EXPERIMENTAL
#include <glm/gtx/string_cast.hpp>

#include <water/water_tile.h>
#include <water/water_renderer.h>
#include <water/water_frame_buffers.h>
#include <particles/particle_master.h>

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

    //models --
    TexturedModel tree = TexturedModel(OBJLoader::load("pine"), ModelTexture(Loader::loadTexture("pine")));
    TexturedModel rock = TexturedModel(OBJLoader::load("rock2"), rockTex);
    TexturedModel fern = TexturedModel(OBJLoader::load("fern"), ModelTexture(Loader::loadTexture("fern"), true, true, 2));
    TexturedModel grass = TexturedModel(OBJLoader::load("grassModel"), ModelTexture(Loader::loadTexture("grassAtlas"), true, true, 4));
    TexturedModel playerModel = TexturedModel(OBJLoader::load("player"), ModelTexture(Loader::loadTexture("playerTexture")));
    TexturedModel lampModel = TexturedModel(OBJLoader::load("lamp"), ModelTexture(Loader::loadTexture("lamp"), false, true));
    //-----------

    std::vector<Entity> entities;

    std::vector<Entity> normalMapEnts;
    auto barrelTex = ModelTexture(Loader::loadTexture("barrel"));
    barrelTex.setShineDamper(5.f);
    barrelTex.setReflectivity(0.5f);
    barrelTex.setNormalMap(Loader::loadTexture("barrelNormal"));
    auto boulderTex = ModelTexture(Loader::loadTexture("boulder"));
    boulderTex.setShineDamper(5.f);
    boulderTex.setReflectivity(0.5f);
    auto crateTex = ModelTexture(Loader::loadTexture("crate"));
    crateTex.setShineDamper(5.f);
    crateTex.setReflectivity(0.5f);
    crateTex.setNormalMap(Loader::loadTexture("crateNormal"));
    boulderTex.setNormalMap(Loader::loadTexture("boulderNormal"));
    normalMapEnts.emplace_back(TexturedModel(OBJLoader::load("barrel", true), barrelTex), glm::vec3(120.f, 0.f, 80.f), glm::vec3(0.f, 180.f, 0.f), 1.f);
    normalMapEnts.emplace_back(TexturedModel(OBJLoader::load("boulder", true), boulderTex), glm::vec3(120.f, 0.f, 110.f), glm::vec3(0.f, 0.f, 0.f), 1.f);
    normalMapEnts.emplace_back(TexturedModel(OBJLoader::load("crate", true), crateTex), glm::vec3(120.f, 0.f, 140.f), glm::vec3(0.f, 0.f, 0.f), 0.04f);

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
    Terrain terrain = Terrain(0, -1, pack, blendMap, "heightmap3");
    //-------------------------------------------------------------------------

    for(int i = 0; i < 40; ++i) {
        auto x = randCoord(0, 800);
        auto z = randCoord(0, 800);
        auto y = terrain.getHeightOfTerrain(x, z);
        entities.emplace_back(tree, glm::vec3(x, y, z), glm::vec3(0.f, randCoord(0, 270), 0.f), randCoord(1, 3));
        x = randCoord(0, 800);
        z = randCoord(0, 800);
        y = terrain.getHeightOfTerrain(x, z);
        entities.emplace_back(rock, glm::vec3(x, y, z), glm::vec3(0.f, 0.f, 0.f), 3.f);
        x = randCoord(0, 800);
        z = randCoord(0, 800);
        y = terrain.getHeightOfTerrain(x, z);
        entities.emplace_back(fern, rand() % 4, glm::vec3(x, y, z), glm::vec3(0.f, 0.f, 0.f), 0.5f);
        x = randCoord(0, 800);
        z = randCoord(0, 800);
        y = terrain.getHeightOfTerrain(x, z);
        entities.emplace_back(grass, rand() % 9, glm::vec3(x, y, z), glm::vec3(0.f, 0.f, 0.f), 3.f);
    }

    //lights -------------
    Light light = Light(glm::vec3(10000.f, 10000.f, 10000.f), glm::vec3(1.3f, 1.3f, 1.3f));
    std::vector<Light> lights {light};

    auto startPos = glm::vec3(200.f, 12.f, 200.f);
    auto startColour = glm::vec3(2.f, 0.f, 0.f);
    for(int i = 0; i < 3; i++) {
        Light light2 = Light(glm::vec3(startPos.x, terrain.getHeightOfTerrain(startPos.x, startPos.z) + 12.f, startPos.z), startColour, glm::vec3(1.f, 0.01f, 0.002f));
        lights.push_back(light2);
        startPos.z += 100.f;
        startColour += glm::vec3(0.f, 0.5f, 0.05f);
    }
    //entities
    for(size_t i = 1; i < lights.size(); ++i) {
        auto pos = lights[i].getPosition();
        pos.y = terrain.getHeightOfTerrain(pos.x, pos.z);
        entities.emplace_back(lampModel, pos, glm::vec3(0, 0, 0), 1.f);
    }
    //---------------------

    MasterRenderer::initialise();
    GuiRenderer::initialise();

    std::vector<GuiTexture> guis;
    GuiTexture gui = GuiTexture(Loader::loadTexture("health"), glm::vec2(-0.85f, 0.9f), glm::vec2(0.15f, 0.25f));
    guis.push_back(gui);

    Shader waterShader = Shader("res/shaders/water.vert", "res/shaders/water.frag");
    WaterTile waterTile = WaterTile(120.f, 160.f, -10.f);
    std::vector<WaterTile> water;
    water.push_back(waterTile);

    WaterFrameBuffers fbos = WaterFrameBuffers();
    WaterRenderer waterRenderer = WaterRenderer(waterShader, MasterRenderer::get_projectionMatrix(), fbos);

    ParticleMaster particleMaster = ParticleMaster(MasterRenderer::get_projectionMatrix());

    // Rendering Loop
    while (WindowManager::shouldClose() == 0) {
        //handle keyboard input
        cam.move();
        player.move(terrain);
        particleMaster.update();

        if(glfwGetKey(WindowManager::getWindow(), GLFW_KEY_P) == GLFW_PRESS) {
            auto pos = player.getPosition();
            particleMaster.addParticle(pos);
        }

        //check_gl_error();

        glEnable(GL_CLIP_DISTANCE0);
        //render to fbos
        {
            //reflection
            fbos.bindReflectionFrameBuffer();
            auto reflectionCam = cam;
            float distance = 2.f * (cam.getPosition().y - waterTile.getHeight());
            auto position = reflectionCam.getPosition() - glm::vec3(0, distance, 0);
            reflectionCam.set_position(position);
            reflectionCam.invertPitch();
            MasterRenderer::renderScene(entities, normalMapEnts, terrain, lights, reflectionCam, player,
                                        glm::vec4{0, 1.f, 0, -waterTile.getHeight() + 1.f});
            fbos.unbindCurrentFrameBuffer();

            //refraction
            fbos.bindRefractionFrameBuffer();
            MasterRenderer::renderScene(entities, normalMapEnts, terrain, lights, cam, player,
                                        glm::vec4{0, -1.f, 0, waterTile.getHeight()});
            fbos.unbindCurrentFrameBuffer();
        }

        //render scene
        glDisable(GL_CLIP_DISTANCE0);
        MasterRenderer::renderScene(entities, normalMapEnts, terrain, lights, cam, player,
                                    glm::vec4{0, 1.f, 0, 10000.f});
        waterRenderer.render(water, cam, light);

        particleMaster.render(cam);

        GuiRenderer::render(guis);

        //check_gl_error();

        //update window
        WindowManager::updateWindow();
        //show fps
        WindowManager::showFPS();
    }

    MasterRenderer::cleanUp();
    GuiRenderer::cleanUp();
    Loader::cleanUp();
    WindowManager::closeWindow();

    return EXIT_SUCCESS;
}
