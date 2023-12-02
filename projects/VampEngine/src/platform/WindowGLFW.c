#include <VampPCH.h>
#include <debug/Logger.h>
#include "WindowGLFW.h"
#include <debug/MemoryTracker.h>
#include <core/Application.h>
#include <core/Window.h>
#include <core/graphics/GraphicsContext.h>
#include <GLFW/glfw3.h>


void ErrorCallback(int errcode, const char *desc)
{
    VAMP_ERROR("[GLFW Error: %d] %s", errcode, desc)
}

void WindowCloseCallback(GLFWwindow *window)
{
    VampWindow *w = (VampWindow *)glfwGetWindowUserPointer(window);

    w->__is_running__ = 0;
}


void VampWindowUpdate(VampWindow *window)
{
    VampWindowGLFW *w = (VampWindowGLFW *)window->__child__;
    glfwSwapBuffers(w->__glfw_window__);
    glfwPollEvents();
}


void VampWindowGLFWDeconstructor(void *windowGLFW)
{
    VampWindowGLFW *w = (VampWindowGLFW *)windowGLFW;
    VampDestroyWindowGLFW(windowGLFW);
}


VampWindowGLFW *VampNewWindowGLFW(VampApplication *app, const char *title, int width, int height)
{
    //Create base Window and override methods.
    VampWindow *new_window              = __VampNewWindow__(app, title, width, height);
    new_window->Update                  = VampWindowUpdate;
    new_window->__child_deconstructor__ = VampWindowGLFWDeconstructor;

    //Create WindowGLFW and init it.
    VampWindowGLFW *VAMP_MALLOC( new_windowGLFW, sizeof(VampWindowGLFW) );
    new_windowGLFW->__base__        = new_window;
    new_windowGLFW->__glfw_window__ = NULL;

    //Final inheritance connection.
    new_window->__child__ = new_windowGLFW;

    if (!glfwInit())
    {
        VAMP_ERROR("GLFW failed to be initialized.");

        //Print a message on release.
        #ifndef VAMP_DEBUG
        printf("GLFW failed to be initialized.\n");
        #endif

        return NULL;
    }

    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);

    new_windowGLFW->__glfw_window__ = glfwCreateWindow(width, height, title, NULL, NULL);

    if (!new_windowGLFW->__glfw_window__)
    {
        VAMP_ERROR("GLFW failed to create the window.");

        //Print a message on release.
        #ifndef VAMP_DEBUG
        printf("GLFW failed to create the window.\n");
        #endif

        return NULL;
    }

    //Make the OpenGL Context.
    glfwMakeContextCurrent(new_windowGLFW->__glfw_window__);

    //Initialize the Graphics Context.
    VampInitGraphicsContext(glfwGetProcAddress);

    glfwSetWindowUserPointer(new_windowGLFW->__glfw_window__, new_window);

    glfwSetErrorCallback(ErrorCallback);

    glfwSetWindowCloseCallback(new_windowGLFW->__glfw_window__, WindowCloseCallback);

    return new_windowGLFW;
}


void VampDestroyWindowGLFW(VampWindowGLFW *window)
{
    glfwTerminate();
    VAMP_FREE(window);
}