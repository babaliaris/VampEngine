#include <VampPCH.h>
#include "WindowGLFW.h"
#include <debug/MemoryTracker.h>
#include <core/Application.h>
#include <GLFW/glfw3.h>


void ErrorCallback(int errcode, const char *desc)
{
    printf("[GLFW Error: %d] %s\n", errcode, desc);
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


VampWindowGLFW *VampNewWindowGLFW(VampWindow *window, const char *title, int width, int height)
{
    VampWindowGLFW *VAMP_MALLOC(new_windowGLFW, sizeof(VampWindowGLFW), window->__app__->__memory_tracker__);

    new_windowGLFW->__app__ = window->__app__;
    new_windowGLFW->__glfw_window__ = NULL;
    window->Update = VampWindowUpdate;

    if (!glfwInit())
    {
        VAMP_ERROR(window->__app__->__engine_logger__, "GLFW failed to be initialized.");

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
        VAMP_ERROR(window->__app__->__engine_logger__, "GLFW failed to create the window.");

        //Print a message on release.
        #ifndef VAMP_DEBUG
        printf("GLFW failed to create the window.\n");
        #endif

        return NULL;
    }

    glfwMakeContextCurrent(new_windowGLFW->__glfw_window__);

    glfwSetWindowUserPointer(new_windowGLFW->__glfw_window__, window);

    glfwSetErrorCallback(ErrorCallback);

    glfwSetWindowCloseCallback(new_windowGLFW->__glfw_window__, WindowCloseCallback);

    return new_windowGLFW;
}


void VampDestroyWindowGLFW(VampWindowGLFW *window)
{
    glfwTerminate();
    VAMP_FREE(window->__app__->__memory_tracker__, window);
}