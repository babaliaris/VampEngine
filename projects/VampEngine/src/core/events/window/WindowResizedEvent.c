#include <VampPCH.h>
#include "WindowResizedEvent.h"
#include <debug/MemoryTracker.h>
#include <sds.h>


static int GetWidth(struct VampWindowResizedEvent *event)
{
    return event->__width__;
}


static int GetHeight(struct VampWindowResizedEvent *event)
{
    return event->__height__;
}


static const char *GetDebugString(struct VampWindowResizedEvent *event)
{
    return event->__debug_str__;
}


static void Deconstructor(void *event)
{
    VampWindowResizedEvent *e = (VampWindowResizedEvent *)event;
    VampDestroyWindowResizedEvent(e);
}





VampWindowResizedEvent *VampNewWindowResizedEvent(VampApplication *app, unsigned int type, int width, int height)
{
    VampEvent *new_event = __VampNewEvent__(app, type);

    VampWindowResizedEvent *VAMP_MALLOC(new_windowresized_event, sizeof(VampWindowResizedEvent));


    new_event->__child__                = new_windowresized_event;
    new_event->__ChildDecontructor__    = Deconstructor;

    new_windowresized_event->__base__   = new_event;
    new_windowresized_event->__width__  = width;
    new_windowresized_event->__height__ = height;
    
    new_windowresized_event->__debug_str__   = sdscatprintf(sdsempty(), 
                                                        "[%s] (%d , %d)", 
                                                        VampEventTypeToString(type), 
                                                        width, height
                                                      );

    new_windowresized_event->GetWidth        = GetWidth;
    new_windowresized_event->GetHeight       = GetHeight;
    new_windowresized_event->GetDebugString  = GetDebugString;

    return new_windowresized_event;
}


void VampDestroyWindowResizedEvent(VampWindowResizedEvent *event)
{
    sdsfree(event->__debug_str__);
    VAMP_FREE(event);
}