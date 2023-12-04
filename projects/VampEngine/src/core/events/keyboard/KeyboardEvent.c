#include <VampPCH.h>
#include "KeyboardEvent.h"
#include <debug/MemoryTracker.h>
#include <sds.h>


static void Deconstructor(void *event)
{
    VampKeyboardEvent *e = (VampKeyboardEvent *)event;
    VampDestroyKeyboardEvent(e);
}


static int GetKeyCode(VampKeyboardEvent *event)
{
    return event->__keycode__;
}

static const char *GetDebugStr(VampKeyboardEvent *event)
{
    return event->__debug_str__;
}


VampKeyboardEvent *VampNewKeyboardEvent(VampApplication *app, unsigned int type, int keycode)
{
    VampEvent *new_event = __VampNewEvent__(app, type);

    VampKeyboardEvent *VAMP_MALLOC(new_keyboard_event, sizeof(VampKeyboardEvent));


    new_event->__child__                = new_keyboard_event;
    new_event->__ChildDecontructor__    = Deconstructor;

    new_keyboard_event->__base__        = new_event;
    new_keyboard_event->__keycode__     = keycode;
    
    new_keyboard_event->__debug_str__   = sdscatprintf(sdsempty(), 
                                                        "[%s] Keycode: %d", 
                                                        VampEventTypeToString(type), 
                                                        keycode
                                                      );
                                                      

    new_keyboard_event->GetKeyCode      = GetKeyCode;
    new_keyboard_event->GetDebugString  = GetDebugStr;

    return new_keyboard_event;
}


void VampDestroyKeyboardEvent(VampKeyboardEvent *event)
{
    sdsfree(event->__debug_str__);
    VAMP_FREE(event);
}