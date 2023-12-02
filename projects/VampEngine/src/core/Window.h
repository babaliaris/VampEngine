#ifndef VAMP_ENGINE_WINDOW_H
#define VAMP_ENGINE_WINDOW_H

/**
 * @file
*/

typedef struct VampApplication VampApplication;
typedef struct VampString VampString;

/**
 * This is the window where stuff are drew into it and that handles the
 * events system.
*/
typedef struct VampWindow
{
    void *__child__; /**< @private This holds the child class object (The one that extends VampWindow)*/
    void (*__child_deconstructor__)(void *child); /**< @private Holds the deconstruction function of the child class.*/

    int __width__; /**< @private*/
    int __height__; /**< @private*/
    char __is_running__; /**< @private*/
    VampString *__title__; /**< @private*/
    VampApplication *__app__; /**< @private*/

    /**
     * Get the width of the window.
     * @param[in] window The VampWindow object.
     * @returns The width of the window.
    */
    int (*GetWidth)(struct VampWindow *window);

    /**
     * Get the height of the window.
     * @param[in] window The VampWindow object.
     * @returns The height of the window.
    */
    int (*GetHeight)(struct VampWindow *window);

    /**
     * Get the title of the window.
     * @param[in] window The VampWindow object.
     * @returns The title of the window.
    */
    const char *(*GetTitle)(struct VampWindow *window);

    /**
     * Swaps the draw buffers and polls the window events.
     * @param[in] window The VampWindow object.
     *
    */
    void (*Update)(struct VampWindow *window);
}
VampWindow;

/**
 * @private
 * This creates a VampWindow object. It is private because this class
 * is meant to be abstract. The child class is responsible for instatiating
 * a VampWindow object.
*/
VampWindow *__VampNewWindow__(VampApplication *app, const char *title, int width, int height);


/**
 * Creates a window implementation based on the operating system. If on Linux for example, this
 * will use the GLFW library to create a window.
 * 
 * @param[in] app The application object - Used as a start pointer point.
 * @param[in] title The VampWindow title.
 * @param[in] width The width of the VampWindow.
 * @param[in] height The height of the VampWindow.
 * 
 * @returns The newly created VampWindow.
*/
VampWindow *VampCreateWindow(VampApplication *app, const char *title, int width, int height);


/**
 * Destroys the window and all it's subclasses that inherits it.
 * 
 * @param[in] window The VampWindow to be destroyed.
*/
void VampDestroyWindow(VampWindow *window);

#endif