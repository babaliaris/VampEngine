#include <VampPCH.h>
#include "WindowMovedEvent.h"
#include <debug/MemoryTracker.h>
#include <sds.h>


static int GetX(struct VampWindowMovedEvent *event)
{
    return event->__x__;
}


static int GetY(struct VampWindowMovedEvent *event)
{
    return event->__y__;
}


static const char *GetDebugString(struct VampWindowMovedEvent *event)
{
    return event->__debug_str__;
}


static void Deconstructor(void *event)
{
    VampWindowMovedEvent *e = (VampWindowMovedEvent *)event;
    VampDestroyWindowMovedEvent(e);
}





VampWindowMovedEvent *VampNewWindowMovedEvent(VampApplication *app, unsigned int type, int x, int y)
{
    VampEvent *new_event = __VampNewEvent__(app, type);

    VampWindowMovedEvent *VAMP_MALLOC(new_windowmoved_event, sizeof(VampWindowMovedEvent));


    new_event->__child__                = new_windowmoved_event;
    new_event->__ChildDecontructor__    = Deconstructor;

    new_windowmoved_event->__base__  = new_event;
    new_windowmoved_event->__x__     = x;
    new_windowmoved_event->__y__     = y;
    
    new_windowmoved_event->__debug_str__   = sdscatprintf(sdsempty(), 
                                                        "[%s] (%d , %d)", 
                                                        VampEventTypeToString(type), 
                                                        x, y
                                                      );

    new_windowmoved_event->GetX            = GetX;
    new_windowmoved_event->GetY            = GetY;
    new_windowmoved_event->GetDebugString  = GetDebugString;

    return new_windowmoved_event;
}


void VampDestroyWindowMovedEvent(VampWindowMovedEvent *event)
{
    sdsfree(event->__debug_str__);
    VAMP_FREE(event);
}