#ifndef VAMP_ENGINE_WINDOW_MOVED_EVENT_H
#define VAMP_ENGINE_WINDOW_MOVED_EVENT_H
#include "../EventBase.h"

/**
 * The VampWindowMovedEvent specific structure.
*/
typedef struct VampWindowMovedEvent
{

    /**
     * Gets the x coordinate.
     * 
     * @param[in] event The event object.
     * @return The x position of the window.
    */
    int (*GetX)(struct VampWindowMovedEvent *event);

    /**
     * Gets the y coordinate.
     * 
     * @param[in] event The event object.
     * @return The y position of the window.
    */
    int (*GetY)(struct VampWindowMovedEvent *event);


    /**
     * Get a representation of the event.
     * 
     * @param[in] event The event object.
     * @returns A string representing the object for debug reasons.
    */
    const char *(*GetDebugString)(struct VampWindowMovedEvent *event);


    VampEvent *__base__; /**< @private*/
    int __x__; /**< @private*/
    int __y__; /**< @private*/
    char *__debug_str__; /**< @private*/
}
VampWindowMovedEvent;



/**
 * Creates a new VampWindowMovedEvent object.
 * 
 * @param[in] app The application object.
 * @param[in] type The VAMP_EVENT type macro.
 * @param[in] x The x position of the window.
 * @param[in] y The y position of the window.
 * 
 * @returns The newly created object.
*/
VampWindowMovedEvent *VampNewWindowMovedEvent(VampApplication *app, unsigned int type, int x, int y);

/**
 * Destroys the VampWindowMovedEvent object.
 * 
 * @param[in] event The VampWindowMovedEvent object to be destroyed.
*/
void VampDestroyWindowMovedEvent(VampWindowMovedEvent *event);

#endif