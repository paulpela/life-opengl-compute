#include "window.h"

void onWindowResize(GLFWwindow* window, int x, int y) {
    glViewport(0, 0, x, y);
}
