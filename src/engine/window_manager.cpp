#include "window_manager.h"
#include <glad/glad.h>
#include <string>
#include <iostream>
#include "Log.h"

GLFWwindow* WindowManager::_window = nullptr;
std::string WindowManager::_title;

void WindowManager::createWindow(const glm::vec2 &size, const std::string &title) {
    _title = title;
    // Load GLFW and Create a Window
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 0);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
    glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);
    _window = glfwCreateWindow((int)size.x, (int)size.y, "Render Engine", nullptr, nullptr);

    // Check for Valid Context
    if (_window == nullptr) {
        LOG(ERR) << "Failed to Create OpenGL Context";
        return;
    }

    // Create Context and Load OpenGL Functions
    glfwMakeContextCurrent(_window);
    gladLoadGL();
    LOG(INFO) << "OpenGL " << glGetString(GL_VERSION);

    //turn vsync off
    //glfwSwapInterval(0);
}

void WindowManager::updateWindow() {
    //if escape is pressed, close the window
    if (glfwGetKey(_window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(_window, true);
    
    //swap buffers
    glfwSwapBuffers(_window);
    glfwPollEvents();
}

//close and destroy window
void WindowManager::closeWindow() {
    glfwSetWindowShouldClose(_window, true);
    glfwDestroyWindow(_window);
    _window = nullptr;
    glfwTerminate();
}

//returns a pointer to the window
GLFWwindow *WindowManager::getWindow() {
    return _window;
}

//returns whether the windows is closed
int WindowManager::shouldClose() {
    return glfwWindowShouldClose(_window);
}

//returns the size of the current window
glm::vec2 WindowManager::getWindowSize() {
    int w, h;
    glfwGetWindowSize(_window, &w, &h);
    return glm::vec2(w, h);
}

//calculates and displays fps
void WindowManager::showUPS() {
        // Static variables are only initialized once ever
        // Used for the size of the average array
        const static int SIZE = 500;
        // Array used to store every frames render time
        static double avgList[SIZE] = { 0.0 };
        // Variables to computer frame render time
        static double previous = 0.0;
        double now = glfwGetTime();
        double average = 0.0;

        // Move every value in the list forward, value position 1 is now in position 0
        for (unsigned int i = 0; i < SIZE - 1; i++)
        {
            avgList[i] = avgList[i + 1];
            average += avgList[i];
        }
        // Store the new time in the last slot
        avgList[SIZE - 1] = now - previous;
        // Add the new time to the average
        average += avgList[SIZE - 1];
        // Divide average my the array size to get the average time
        average /= SIZE;

        // Update the title with the FPS
        glfwSetWindowTitle(_window, (_title + " | FPS: " + std::to_string(1.0f / average)).c_str());

        // Store the current time
        previous = now;
}
