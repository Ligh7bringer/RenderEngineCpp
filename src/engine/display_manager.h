#ifndef RENDERENGINE_DISPLAY_MANAGER_H
#define RENDERENGINE_DISPLAY_MANAGER_H

#include <GLFW/glfw3.h>

class DisplayManager {
public:
    void create_display();
    void update_display();
    void close_display();
    int should_close();

    GLFWwindow* get_window() const;
private:
    const int WIDTH = 1280;
    const int HEIGHT = 720;
    GLFWwindow* _window;
};


#endif //RENDERENGINE_DISPLAY_MANAGER_H
