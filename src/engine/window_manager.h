#ifndef RENDERENGINE_DISPLAY_MANAGER_H
#define RENDERENGINE_DISPLAY_MANAGER_H

#include <GLFW/glfw3.h>
#include <glm/vec2.hpp>
#include <string>

class WindowManager {
public:
    static void createWindow(const glm::vec2 &size, const std::string &title);
    static void updateWindow();
    static void closeWindow();
    static int shouldClose();

    static glm::vec2 getWindowSize();
    static GLFWwindow* getWindow();
    static void showUPS();

    static double getDeltaTime();

protected:
    static GLFWwindow* _window;
    static std::string _title;

    static double _lastFrameTime;
    static double _deltaTime;
};


#endif //RENDERENGINE_DISPLAY_MANAGER_H
