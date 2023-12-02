#ifndef VAMP_ENGINE_WINDOW_GLFW
#define VAMP_ENGINE_WINDOW_GLFW

typedef struct GLFWwindow GLFWwindow;
typedef struct VampWindow VampWindow;
typedef struct VampApplication VampApplication;


/**
 * The implementation of a GLFW window. Inherits VampWindow.
*/
typedef struct VampWindowGLFW
{
    VampWindow *__base__; /**< @private*/
    GLFWwindow *__glfw_window__; /**< @private*/
}
VampWindowGLFW;


/**
 * Creates a VampWindowGLFW object.
 * 
 * @param[in] app The application object - Used as a start pointer point.
 * @param[in] title The VampWindow title.
 * @param[in] width The width of the VampWindow.
 * @param[in] height The height of the VampWindow.
 * 
 * @returns The newly created VampWindowGLFW object.
*/
VampWindowGLFW *VampNewWindowGLFW(VampApplication *app, const char *title, int width, int height);


/**
 * Destroys a VampWindowGLFW object.
 * 
 * @param[in] window The VampWindowGLFW object to be destroyed.
*/
void VampDestroyWindowGLFW(VampWindowGLFW *window);

#endif