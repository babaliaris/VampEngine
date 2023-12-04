#include <VampPCH.h>
#include "EventBase.h"
#include <debug/MemoryTracker.h>


static VampApplication *GetApp(VampEvent *event)
{
    return event->__app__;
}


static void Dispatch(VampEvent *event, unsigned int type, VampEventDispatchFunc callback)
{
    if (callback && event->__type__ == type)
        event->__has_been_handled__ = callback(event->__child__);
}


VampEvent *__VampNewEvent__(VampApplication *app, unsigned int type)
{
    VampEvent *VAMP_MALLOC(new_event, sizeof(VampEvent));

    new_event->__app__                  = app;
    new_event->__type__                 = type;
    new_event->__has_been_handled__     = 0;
    new_event->__child__                = NULL; //to be overridden.
    new_event->__ChildDecontructor__    = NULL; //to be overridden.

    new_event->GetApp           = GetApp;
    new_event->Dispatch         = Dispatch;

    return new_event;
}

void VampDestroyEvent(VampEvent *event)
{
    event->__ChildDecontructor__(event->__child__);
    VAMP_FREE(event);
}


const char *VampEventTypeToString(unsigned int type)
{
    switch (type)
    {
        case VAMP_EVENT_KEY_PRESSED:
            return "VAMP_EVENT_KEY_PRESSED";

        case VAMP_EVENT_KEY_RELEASED:
            return "VAMP_EVENT_KEY_RELEASED";

        case VAMP_EVENT_KEY_REPEAT:
            return "VAMP_EVENT_KEY_REPEAT";

        case VAMP_EVENT_MOUSE_PRESSED:
            return "VAMP_EVENT_MOUSE_PRESSED";

        case VAMP_EVENT_MOUSE_RELEASED:
            return "VAMP_EVENT_MOUSE_RELEASED";

        case VAMP_EVENT_WINDOW_FOCUSED:
            return "VAMP_EVENT_WINDOW_FOCUSED";

        case VAMP_EVENT_WINDOW_LOST_FOCUS:
            return "VAMP_EVENT_WINDOW_LOST_FOCUS";

        case VAMP_EVENT_WINDOW_MINIMIZED:
            return "VAMP_EVENT_WINDOW_MINIMIZED";

        case VAMP_EVENT_WINDOW_RESIZED:
            return "VAMP_EVENT_WINDOW_RESIZED";
        
        default:
            return "";
    }
}