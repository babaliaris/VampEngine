#ifndef VAMP_ENGINE_WINDOW_GLFW
#define VAMP_ENGINE_WINDOW_GLFW

typedef struct GLFWwindow GLFWwindow;
typedef struct VampWindow VampWindow;
typedef struct VampApplication VampApplication;

typedef struct VampWindowGLFW
{
    VampWindow *__base__;
    GLFWwindow *__glfw_window__;
}
VampWindowGLFW;


VampWindowGLFW *VampNewWindowGLFW(VampApplication *app, const char *title, int width, int height);

void VampDestroyWindowGLFW(VampWindowGLFW *window);

#endif