#ifndef VAMP_ENGINE_WINDOW_EVENT_H
#define VAMP_ENGINE_WINDOW_EVENT_H
#include "../EventBase.h"

/**
 * The VampWindowEvent specific structure.
*/
typedef struct VampWindowEvent
{
    /**
     * Get a representation of the event.
     * 
     * @param[in] event The event object.
     * @returns A string representing the object for debug reasons.
    */
    const char *(*GetDebugString)(struct VampWindowEvent *event);


    VampEvent *__base__; /**< @private*/
    char *__debug_str__; /**< @private*/
}
VampWindowEvent;



/**
 * Creates a new VampWindowEvent object.
 * 
 * @param[in] app The application object.
 * @param[in] type The VAMP_EVENT type macro.
 * 
 * @returns The newly created object.
*/
VampWindowEvent *VampNewWindowEvent(VampApplication *app, unsigned int type);

/**
 * Destroys the VampWindowEvent object.
 * 
 * @param[in] event The VampWindowEvent object to be destroyed.
*/
void VampDestroyWindowEvent(VampWindowEvent *event);

#endif