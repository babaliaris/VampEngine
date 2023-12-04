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



static int GetWidth(VampWindow *window)
{
    return window->__width__;
}

static int GetHeight(VampWindow *window)
{
    return window->__height__;
}

static const char *GetWindowTitle(VampWindow *window)
{
    return window->__title__->__str__;
}

VampWindow *__VampNewWindow__(VampApplication *app, const char *title, int width, int height)
{
    VampWindow *VAMP_MALLOC( new_window, sizeof(VampWindow) );

    new_window->__app__                 = app;
    new_window->__width__               = width;
    new_window->__height__              = height;
    new_window->__is_running__          = 1;
    new_window->__title__               = VampNewString(title);
    new_window->__child__               = NULL; //to be overridden.
    new_window->__child_deconstructor__ = NULL; //to be overridden.
    new_window->__event_callback__      = NULL; //will be set by the application.

    new_window->Update      = NULL;
    new_window->GetWidth    = GetWidth;
    new_window->GetHeight   = GetHeight;
    new_window->GetTitle    = GetWindowTitle;

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