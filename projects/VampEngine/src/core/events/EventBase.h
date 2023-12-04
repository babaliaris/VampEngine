#ifndef VAMP_ENGINE_EVENT_BASE_H
#define VAMP_ENGINE_EVENT_BASE_H

/**
 * @file
*/

#define VAMP_EVENT_KEY_PRESSED              0
#define VAMP_EVENT_KEY_RELEASED             1
#define VAMP_EVENT_KEY_REPEAT               2
#define VAMP_EVENT_MOUSE_PRESSED            3
#define VAMP_EVENT_MOUSE_RELEASED           4
#define VAMP_EVENT_WINDOW_FOCUSED           5
#define VAMP_EVENT_WINDOW_LOST_FOCUS        6
#define VAMP_EVENT_WINDOW_RESIZED           7
#define VAMP_EVENT_WINDOW_MINIMIZED         8


/**
 * User Defined Function: This is the callback function that
 * the VampEvent Dispatcher will call.
 * 
 * @param[in] event The event object that has been dispatched.
 * @returns 1 (true) to stop propagating this event higher to the layers list. 0 (false) otherwise.
*/
typedef char (*VampEventDispatchFunc)(void *event);


typedef struct VampApplication VampApplication;


/**
 * Event structure.
*/
typedef struct VampEvent
{
    /**
     * Get the application object.
     * 
     * @param[in] event The event object.
     * @returns The VampApplication object.
    */
    VampApplication *(*GetApp)(struct VampEvent *event);


    /**
     * Dispatches the event into a callback that gets called only if the event type
     * matches the type parameter of the Despatch() method.
     * 
     * @param[in] event The VampEvent object to be dispatched.
     * @param[in] type The VAMP_EVENT type that is required.
     * @param[in] callback The VampEventDispatchFunc() user defined function.
    */
    void (*Dispatch)(struct VampEvent *event, unsigned int type, VampEventDispatchFunc callback);



    void *__child__; /**< @private*/
    void (*__ChildDecontructor__)(void *child); /**< @private*/
    VampApplication *__app__; /**< @private*/
    unsigned int __type__; /**< @private*/
    char __has_been_handled__; /**< @private*/
}
VampEvent;


/**
 * @private
*/
VampEvent *__VampNewEvent__(VampApplication *app, unsigned int type);


/**
 * Destroys the VampEvent object.
 * 
 * @param[in] event
*/
void VampDestroyEvent(VampEvent *event);



/**
 * Return a sting representing the VAMP_EVENT type definition.
 * 
 * @param[in] type the VAMP_EVENT type definition.
*/
const char *VampEventTypeToString(unsigned int type);


#endif