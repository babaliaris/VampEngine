#include <VampPCH.h>
#include "Window.h"
#include <VampString.h>
#include <debug/MemoryTracker.h>
#include <core/Application.h>


#ifdef VAMP_LINUX
#include <platform/WindowGLFW.h>
#endif

#ifdef VAMP_WINDOWS
#include <platform/WindowGLFW.h>
#endif



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

VampWindow *__VampNewWindow__(VampApplication *app, const char *title, int width, int height)
{
    VampWindow *VAMP_MALLOC( new_window, sizeof(VampWindow) );

    new_window->__app__         = app;
    new_window->__width__       = width;
    new_window->__height__      = height;
    new_window->__is_running__  = 1;
    new_window->__title__       = VampNewString(title);


    new_window->GetWidth    = VampWindowGetWidth;
    new_window->GetHeight   = VampWindowGetHeight;
    new_window->GetTitle    = VampGetWindowTitle;

    return new_window;
}


VampWindow *VampCreateWindow(VampApplication *app, const char *title, int width, int height)
{
    #ifdef VAMP_LINUX
    return VampNewWindowGLFW(app, title, width, height)->__base__;
    #endif

    #ifdef VAMP_WINDOWS
    return VampNewWindowGLFW(app, title, width, height)->__base__;
    #endif
}


void VampDestroyWindow(VampWindow *window)
{
    VampDestroyString(window->__title__);

    window->__child_deconstructor__(window->__child__);

    VAMP_FREE(window);
}