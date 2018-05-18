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
    static const glm::vec2 &getMouseWheelDelta();
    static const glm::vec2 &getCursorDelta();
    static const glm::vec2 &getMouseWheel();
    static void resetMouseWheel();

protected:
    static GLFWwindow* _window;
    static std::string _title;

    static double _lastFrameTime;
    static double _deltaTime;

    static glm::vec2 _scrollOld;
    static glm::vec2 _scrollDelta;

    static glm::vec2 _cursorPos;
    static glm::vec2 _cursorDelta;

private:
    static void scroll_callback(GLFWwindow* window, double xoffset, double yoffset);
    static void cursor_position_callback(GLFWwindow* window, double xpos, double ypos);
};


#endif //RENDERENGINE_DISPLAY_MANAGER_H
