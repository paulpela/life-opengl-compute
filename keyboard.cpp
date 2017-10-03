#include "keyboard.h"

bool paused = false;

int magnification = 1;

bool directionalKeys[4];

void keyCallback(GLFWwindow* window, int key, int scancode, int action, int mods) {
    if(action == GLFW_PRESS) {
        if(key == GLFW_KEY_ESCAPE) {
            glfwSetWindowShouldClose(window, GLFW_TRUE);
        }
        if(key == GLFW_KEY_SPACE) {
            paused = !paused;
        }
    }

    if(action != GLFW_RELEASE) {
        if(key == GLFW_KEY_UP) {
            directionalKeys[0] = true;
        }
        if(key == GLFW_KEY_DOWN) {
            directionalKeys[1] = true;
        }
        if(key == GLFW_KEY_LEFT) {
            directionalKeys[2] = true;
        }
        if(key == GLFW_KEY_RIGHT) {
            directionalKeys[3] = true;
        }
    }

    if(action == GLFW_RELEASE) {
        if(key == GLFW_KEY_UP) {
            directionalKeys[0] = false;
        }
        if(key == GLFW_KEY_DOWN) {
            directionalKeys[1] = false;
        }
        if(key == GLFW_KEY_LEFT) {
            directionalKeys[2] = false;
        }
        if(key == GLFW_KEY_RIGHT) {
            directionalKeys[3] = false;
        }

    }
}

