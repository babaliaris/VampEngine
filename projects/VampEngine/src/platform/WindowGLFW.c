#include <VampPCH.h>
#include <debug/Logger.h>
#include "WindowGLFW.h"
#include <debug/MemoryTracker.h>
#include <core/Application.h>
#include <core/Window.h>
#include <core/graphics/GraphicsContext.h>
#include <GLFW/glfw3.h>
#include <core/events/Events.h>


static void ErrorCallback(int errcode, const char *desc);
static void KeyCallback(GLFWwindow* window, int key, int scancode, int action, int mods);
static void MouseButtonCallback(GLFWwindow* window, int button, int action, int mods);
static void CursorPosCallback(GLFWwindow* window, double xpos, double ypos);
static void WindowFocusCallback(GLFWwindow* window, int focused);
static void WindowCloseCallback(GLFWwindow *window);
static void WindowMaximizedCallback(GLFWwindow* window, int maximized);
static void WindowPosCallback(GLFWwindow* window, int xpos, int ypos);
static void WindowSizeCallback(GLFWwindow* window, int width, int height);
static void WindowMinizedCallback(GLFWwindow* window, int iconified);



//=================================================|WindowGLFW|=================================================//
static void WindowUpdate(VampWindow *base)
{
    VampWindowGLFW *this = (VampWindowGLFW *)base->__child__;
    glfwSwapBuffers(this->__glfw_window__);
    glfwPollEvents();
}


static void WindowGLFWDeconstructor(void *this)
{
    VampWindowGLFW *t = (VampWindowGLFW *)this;
    VampDestroyWindowGLFW(t);
}


VampWindowGLFW *VampNewWindowGLFW(VampApplication *app, const char *title, int width, int height)
{
    //Create base Window and override methods.
    VampWindow *new_window              = __VampNewWindow__(app, title, width, height);
    new_window->Update                  = WindowUpdate;
    new_window->__child_deconstructor__ = WindowGLFWDeconstructor;

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

    glfwSetKeyCallback(new_windowGLFW->__glfw_window__, KeyCallback);

    glfwSetMouseButtonCallback(new_windowGLFW->__glfw_window__, MouseButtonCallback);

    glfwSetCursorPosCallback(new_windowGLFW->__glfw_window__, CursorPosCallback);

    glfwSetWindowFocusCallback(new_windowGLFW->__glfw_window__, WindowFocusCallback);

    glfwSetWindowCloseCallback(new_windowGLFW->__glfw_window__, WindowCloseCallback);

    glfwSetWindowMaximizeCallback(new_windowGLFW->__glfw_window__, WindowMaximizedCallback);

    glfwSetWindowPosCallback(new_windowGLFW->__glfw_window__, WindowPosCallback);

    glfwSetWindowSizeCallback(new_windowGLFW->__glfw_window__, WindowSizeCallback);

    glfwSetWindowIconifyCallback(new_windowGLFW->__glfw_window__, WindowMinizedCallback);



    return new_windowGLFW;
}


void VampDestroyWindowGLFW(VampWindowGLFW *window)
{
    glfwTerminate();
    VAMP_FREE(window);
}
//=================================================|WindowGLFW|=================================================//










//=====================================|GLFW Callback Funcion Definitions|======================================//
static void ErrorCallback(int errcode, const char *desc)
{
    VAMP_ERROR("[GLFW Error: %d] %s", errcode, desc);
}



static void KeyCallback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
    VampWindow *w = (VampWindow *)glfwGetWindowUserPointer(window);

    switch (action)
    {
        case GLFW_PRESS:
        {
            VampKeyboardEvent *event = VampNewKeyboardEvent(w->__app__, VAMP_EVENT_KEY_PRESSED, key);
            w->__event_callback__(event->__base__);
            VampDestroyEvent(event->__base__);
            break;
        }

        case GLFW_RELEASE:
        {
            VampKeyboardEvent *event = VampNewKeyboardEvent(w->__app__, VAMP_EVENT_KEY_RELEASED, key);
            w->__event_callback__(event->__base__);
            VampDestroyEvent(event->__base__);
            break;
        }

        case GLFW_REPEAT:
        {
            VampKeyboardEvent *event = VampNewKeyboardEvent(w->__app__, VAMP_EVENT_KEY_REPEAT, key);
            w->__event_callback__(event->__base__);
            VampDestroyEvent(event->__base__);
            break;
        }
        
        default:
            break;
    }
}



static void MouseButtonCallback(GLFWwindow* window, int button, int action, int mods)
{
    VampWindow *w = (VampWindow *)glfwGetWindowUserPointer(window);

    switch (action)
    {
        case GLFW_PRESS:
        {
            VampMouseButtonEvent *event = VampNewMouseButtonEvent(w->__app__, VAMP_EVENT_MOUSE_PRESSED, button);
            w->__event_callback__(event->__base__);
            VampDestroyEvent(event->__base__);
            break;
        }

        case GLFW_RELEASE:
        {
            VampMouseButtonEvent *event = VampNewMouseButtonEvent(w->__app__, VAMP_EVENT_MOUSE_RELEASED, button);
            w->__event_callback__(event->__base__);
            VampDestroyEvent(event->__base__);
            break;
        }
        
        default:
            break;
    }
}


static void CursorPosCallback(GLFWwindow* window, double xpos, double ypos)
{
    VampWindow *w = (VampWindow *)glfwGetWindowUserPointer(window);

    VampMousePosEvent *event = VampNewMousePosEvent(w->__app__, VAMP_EVENT_MOUSE_POS, xpos, ypos);
    w->__event_callback__(event->__base__);
    VampDestroyEvent(event->__base__);
}


static void WindowFocusCallback(GLFWwindow* window, int focused)
{
    VampWindow *w = (VampWindow *)glfwGetWindowUserPointer(window);

    switch (focused)
    {
        case GLFW_TRUE:
        {
            VampWindowEvent *event = VampNewWindowEvent(w->__app__, VAMP_EVENT_WINDOW_FOCUSED);
            w->__event_callback__(event->__base__);
            VampDestroyEvent(event->__base__);
            break;
        }

        case GLFW_FALSE:
        {
            VampWindowEvent *event = VampNewWindowEvent(w->__app__, VAMP_EVENT_WINDOW_LOST_FOCUS);
            w->__event_callback__(event->__base__);
            VampDestroyEvent(event->__base__);
            break;
        }
    
    default:
        break;
    }
}


static void WindowCloseCallback(GLFWwindow *window)
{
    VampWindow *w = (VampWindow *)glfwGetWindowUserPointer(window);

    VampWindowEvent *event = VampNewWindowEvent(w->__app__, VAMP_EVENT_WINDOW_CLOSE);
    w->__event_callback__(event->__base__);
    VampDestroyEvent(event->__base__);
}


static void WindowMaximizedCallback(GLFWwindow* window, int maximized)
{
    VampWindow *w = (VampWindow *)glfwGetWindowUserPointer(window);

    if (maximized == GLFW_TRUE)
    {
        VampWindowEvent *event = VampNewWindowEvent(w->__app__, VAMP_EVENT_WINDOW_MAXIMIZED);
        w->__event_callback__(event->__base__);
        VampDestroyEvent(event->__base__);
    }


    else
    {
        VampWindowEvent *event = VampNewWindowEvent(w->__app__, VAMP_EVENT_WINDOW_RESTORED);
        w->__event_callback__(event->__base__);
        VampDestroyEvent(event->__base__);
    }
}


static void WindowMinizedCallback(GLFWwindow* window, int iconified)
{
    VampWindow *w = (VampWindow *)glfwGetWindowUserPointer(window);

    if (iconified == GLFW_TRUE)
    {
        VampWindowEvent *event = VampNewWindowEvent(w->__app__, VAMP_EVENT_WINDOW_MINIMIZED);
        w->__event_callback__(event->__base__);
        VampDestroyEvent(event->__base__);
    }


    else
    {
        VampWindowEvent *event = VampNewWindowEvent(w->__app__, VAMP_EVENT_WINDOW_RESTORED);
        w->__event_callback__(event->__base__);
        VampDestroyEvent(event->__base__);
    }
}


static void WindowPosCallback(GLFWwindow* window, int xpos, int ypos)
{
    VampWindow *w = (VampWindow *)glfwGetWindowUserPointer(window);

    VampWindowMovedEvent *event = VampNewWindowMovedEvent(w->__app__, VAMP_EVENT_WINDOW_MOVED, xpos, ypos);
    w->__event_callback__(event->__base__);
    VampDestroyEvent(event->__base__);
}


static void WindowSizeCallback(GLFWwindow* window, int width, int height)
{
    VampWindow *w = (VampWindow *)glfwGetWindowUserPointer(window);

    VampWindowResizedEvent *event = VampNewWindowResizedEvent(w->__app__, VAMP_EVENT_WINDOW_RESIZED, width, height);
    w->__event_callback__(event->__base__);
    VampDestroyEvent(event->__base__);
}
//=====================================|GLFW Callback Funcion Definitions|======================================//
