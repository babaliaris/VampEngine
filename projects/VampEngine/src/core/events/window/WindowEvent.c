#include <VampPCH.h>
#include "WindowEvent.h"
#include <sds.h>
#include <debug/MemoryTracker.h>


static const char *GetDebugString(struct VampWindowEvent *event)
{
    return event->__debug_str__;
}


static void Deconstructor(void *event)
{
    VampWindowEvent *e = (VampWindowEvent *)event;
    VampDestroyWindowEvent(e);
}


VampWindowEvent *VampNewWindowEvent(VampApplication *app, unsigned int type)
{
    VampEvent *new_event = __VampNewEvent__(app, type);

    VampWindowEvent *VAMP_MALLOC(new_window_event, sizeof(VampWindowEvent));


    new_event->__child__                = new_window_event;
    new_event->__ChildDecontructor__    = Deconstructor;

    new_window_event->__base__            = new_event;
    
    new_window_event->__debug_str__   = sdscatprintf(sdsempty(), 
                                                        "[%s]", 
                                                        VampEventTypeToString(type)
                                                      );

    new_window_event->GetDebugString  = GetDebugString;

    return new_window_event;
}


void VampDestroyWindowEvent(VampWindowEvent *event)
{
    sdsfree(event->__debug_str__);
    VAMP_FREE(event);
}