#ifndef VAMP_ENGINE_KEYBOARD_EVENT_H
#define VAMP_ENGINE_KEYBOARD_EVENT_H
#include "../EventBase.h"

/**
 * The keyboard specific structure.
*/
typedef struct VampKeyboardEvent
{

    /**
     * Gets the keycode of the event.
     * 
     * @param[in] event The event object.
     * @return The keycode.
    */
    int (*GetKeyCode)(struct VampKeyboardEvent *event);


    /**
     * Get a representation of the event.
     * 
     * @param[in] event The event object.
     * @returns A string representing the object for debug reasons.
    */
    const char *(*GetDebugString)(struct VampKeyboardEvent *event);


    VampEvent *__base__; /**< @private*/
    int __keycode__; /**< @private*/
    char *__debug_str__; /**< @private*/
}
VampKeyboardEvent;



/**
 * Creates a new VampKeyboardEvent object.
 * 
 * @param[in] app The application object.
 * @param[in] type The VAMP_EVENT type macro.
 * @param[in] keycode The keyboard keycode.
 * 
 * @returns The newly created object.
*/
VampKeyboardEvent *VampNewKeyboardEvent(VampApplication *app, unsigned int type, int keycode);

/**
 * Destroys the VampKeyboardEvent object.
 * 
 * @param[in] event The VampKeyboardEvent object to be destroyed.
*/
void VampDestroyKeyboardEvent(VampKeyboardEvent *event);


#endif