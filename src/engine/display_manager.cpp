#include "display_manager.h"
#include <glad/glad.h>
#include <string>
#include <iostream>
#include "Log.h"

void DisplayManager::create_display() {
    // Load GLFW and Create a Window
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 0);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
    glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);
    _window = glfwCreateWindow(WIDTH, HEIGHT, "Render Engine", nullptr, nullptr);

    // Check for Valid Context
    if (_window == nullptr) {
        LOG(ERROR) << "Failed to Create OpenGL Context";
        return;
    }

    // Create Context and Load OpenGL Functions
    glfwMakeContextCurrent(_window);
    gladLoadGL();
    LOG(INFO) << "OpenGL " << glGetString(GL_VERSION);
}

void DisplayManager::update_display() {
    //if escape is pressed, close the window
    if (glfwGetKey(_window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(_window, true);

    // flip buffers
    glfwSwapBuffers(_window);
    glfwPollEvents();
}

//close and destroy window
void DisplayManager::close_display() {
    glfwSetWindowShouldClose(_window, true);
    glfwDestroyWindow(_window);
    _window = nullptr;
    glfwTerminate();
}

//returns a pointer to the window
GLFWwindow *DisplayManager::get_window() const {
    return _window;
}

//returns whether the windows is closed
int DisplayManager::should_close() {
    return glfwWindowShouldClose(_window);
}
