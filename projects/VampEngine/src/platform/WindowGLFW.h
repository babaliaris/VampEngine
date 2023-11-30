#ifndef VAMP_ENGINE_WINDOW_GLFW
#define VAMP_ENGINE_WINDOW_GLFW
#include <core/Window.h>
#include <core/Application.h>

typedef struct GLFWwindow GLFWwindow;

typedef struct VampWindowGLFW
{
    GLFWwindow *__glfw_window__;
    VampApplication *__app__;
}
VampWindowGLFW;


VampWindowGLFW *VampNewWindowGLFW(VampWindow *window, const char *title, int width, int height);

void VampDestroyWindowGLFW(VampWindowGLFW *window);

#endif