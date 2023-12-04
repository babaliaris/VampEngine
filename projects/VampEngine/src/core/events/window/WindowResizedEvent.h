#ifndef VAMP_ENGINE_WINDOW_RESIZED_EVENT_H
#define VAMP_ENGINE_WINDOW_RESIZED_EVENT_H
#include "../EventBase.h"

/**
 * The VampWindowResizedEvent specific structure.
*/
typedef struct VampWindowResizedEvent
{

    /**
     * Gets the width of the window.
     * 
     * @param[in] event The event object.
     * @return The width of the window.
    */
    int (*GetWidth)(struct VampWindowResizedEvent *event);

    /**
     * Gets the height of the window.
     * 
     * @param[in] event The event object.
     * @return The height of the window.
    */
    int (*GetHeight)(struct VampWindowResizedEvent *event);


    /**
     * Get a representation of the event.
     * 
     * @param[in] event The event object.
     * @returns A string representing the object for debug reasons.
    */
    const char *(*GetDebugString)(struct VampWindowResizedEvent *event);


    VampEvent *__base__; /**< @private*/
    int __width__; /**< @private*/
    int __height__; /**< @private*/
    char *__debug_str__; /**< @private*/
}
VampWindowResizedEvent;



/**
 * Creates a new VampWindowResizedEvent object.
 * 
 * @param[in] app The application object.
 * @param[in] type The VAMP_EVENT type macro.
 * @param[in] width The width of the window.
 * @param[in] height The height of the window.
 * 
 * @returns The newly created object.
*/
VampWindowResizedEvent *VampNewWindowResizedEvent(VampApplication *app, unsigned int type, int width, int height);

/**
 * Destroys the VampWindowResizedEvent object.
 * 
 * @param[in] event The VampWindowResizedEvent object to be destroyed.
*/
void VampDestroyWindowResizedEvent(VampWindowResizedEvent *event);

#endif