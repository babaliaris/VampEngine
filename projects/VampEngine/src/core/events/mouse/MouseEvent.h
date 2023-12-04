#ifndef VAMP_ENGINE_MOUSE_EVENT_H
#define VAMP_ENGINE_MOUSE_EVENT_H
#include "../EventBase.h"

/**
 * The MouseButtonEvent specific structure.
*/
typedef struct VampMouseButtonEvent
{

    /**
     * Gets the mouse button code.
     * 
     * @param[in] event The event object.
     * @return The button code.
    */
    int (*GetButtonCode)(struct VampMouseButtonEvent *event);


    /**
     * Get a representation of the event.
     * 
     * @param[in] event The event object.
     * @returns A string representing the object for debug reasons.
    */
    const char *(*GetDebugString)(struct VampMouseButtonEvent *event);


    VampEvent *__base__; /**< @private*/
    int __mouse_btn_code__; /**< @private*/
    char *__debug_str__; /**< @private*/
}
VampMouseButtonEvent;



/**
 * Creates a new VampMouseButtonEvent object.
 * 
 * @param[in] app The application object.
 * @param[in] type The VAMP_EVENT type macro.
 * @param[in] mouse_btn_code The button code.
 * 
 * @returns The newly created object.
*/
VampMouseButtonEvent *VampNewMouseButtonEvent(VampApplication *app, unsigned int type, int mouse_btn_code);

/**
 * Destroys the VampMouseButtonEvent object.
 * 
 * @param[in] event The VampMouseButtonEvent object to be destroyed.
*/
void VampDestroyMouseButtonEvent(VampMouseButtonEvent *event);










/**
 * The MousePosEvent specific structure.
*/
typedef struct VampMousePosEvent
{

    /**
     * Gets the x coordinate.
     * 
     * @param[in] event The event object.
     * @return The x position of the mouse.
    */
    double (*GetX)(struct VampMousePosEvent *event);

    /**
     * Gets the y coordinate.
     * 
     * @param[in] event The event object.
     * @return The y position of the mouse.
    */
    double (*GetY)(struct VampMousePosEvent *event);


    /**
     * Get a representation of the event.
     * 
     * @param[in] event The event object.
     * @returns A string representing the object for debug reasons.
    */
    const char *(*GetDebugString)(struct VampMousePosEvent *event);


    VampEvent *__base__; /**< @private*/
    double __mouse_x__; /**< @private*/
    double __mouse_y__; /**< @private*/
    char *__debug_str__; /**< @private*/
}
VampMousePosEvent;



/**
 * Creates a new VampMousePosEvent object.
 * 
 * @param[in] app The application object.
 * @param[in] type The VAMP_EVENT type macro.
 * @param[in] x The x position of the mouse.
 * @param[in] y The y position of the mouse.
 * 
 * @returns The newly created object.
*/
VampMousePosEvent *VampNewMousePosEvent(VampApplication *app, unsigned int type, double x, double y);

/**
 * Destroys the VampMousePosEvent object.
 * 
 * @param[in] event The VampMousePosEvent object to be destroyed.
*/
void VampDestroyMousePosEvent(VampMousePosEvent *event);


#endif
