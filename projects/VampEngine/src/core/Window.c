#include <VampPCH.h>
#include "Window.h"
#include <debug/MemoryTracker.h>
#include <core/Application.h>


#ifdef VAMP_LINUX
#include <platform/WindowGLFW.h>
#endif

#ifdef VAMP_WINDOWS
#include <platform/WindowGLFW.h>
#endif

#define VAMP_WINDOW_TYPE_GLFW 0
#define VAMP_WINDOW_TYPE_WINDOWS 1
#define VAMP_WINDOW_TYPE_MAC 2


int VampWindowGetWidth(VampWindow *window)
{
    return window->__width__;
}

int VampWindowGetHeight(VampWindow *window)
{
    return window->__height__;
}

const char *VampGetWindowTitle(VampWindow *window)
{
    return window->__title__->__str__;
}

VampWindow *VampNewWindow(VampApplication *app, const char *title, int width, int height)
{
    VampWindow *VAMP_MALLOC(new_window, sizeof(VampWindow), app->__memory_tracker__);

    new_window->__app__ = app;
    new_window->__width__ = width;
    new_window->__height__ = height;
    new_window->__is_running__ = 1;
    new_window->__title__ = VampNewString(title);


    new_window->GetWidth = VampWindowGetWidth;
    new_window->GetHeight = VampWindowGetHeight;
    new_window->GetTitle = VampGetWindowTitle;

    #ifdef VAMP_LINUX
    new_window->__child_type__ = VAMP_WINDOW_TYPE_GLFW;
    new_window->__child__ = VampNewWindowGLFW(new_window, title, width, height);
    #endif

    #ifdef VAMP_WINDOWS
    new_window->__child_type__ = VAMP_WINDOW_TYPE_GLFW;
    new_window->__child__ = VampNewWindowGLFW(new_window, title, width, height);
    #endif

    return new_window;
}


void VampDestroyWindow(VampWindow *window)
{
    VampDestroyString(window->__title__);

    switch (window->__child_type__)
    {
        case VAMP_WINDOW_TYPE_GLFW:
            #ifdef VAMP_LINUX
            VampDestroyWindowGLFW(window->__child__);
            #endif
            break;

        case VAMP_WINDOW_TYPE_WINDOWS:
            #ifdef VAMP_WINDOWS
            VampDestroyWindowGLFW(window->__child__);
            #endif
            break;
        
        default:
            break;
    }

    VAMP_FREE(window->__app__->__memory_tracker__, window);
}