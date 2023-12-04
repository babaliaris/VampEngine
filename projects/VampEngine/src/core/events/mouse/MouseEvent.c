#include <VampPCH.h>
#include "MouseEvent.h"
#include <debug/MemoryTracker.h>
#include <sds.h>



static int GetButtonCode(struct VampMouseButtonEvent *event)
{
    return event->__mouse_btn_code__;
}



static const char *GetMouseButtonDebugString(struct VampMouseButtonEvent *event)
{
    return event->__debug_str__;
}


static void DeconstructorMouseButtonEvent(void *event)
{
    VampMouseButtonEvent *e = (VampMouseButtonEvent *)event;
    VampDestroyMouseButtonEvent(e);
}


VampMouseButtonEvent *VampNewMouseButtonEvent(VampApplication *app, unsigned int type, int mouse_btn_code)
{
    VampEvent *new_event = __VampNewEvent__(app, type);

    VampMouseButtonEvent *VAMP_MALLOC(new_mousebtn_event, sizeof(VampMouseButtonEvent));


    new_event->__child__                = new_mousebtn_event;
    new_event->__ChildDecontructor__    = DeconstructorMouseButtonEvent;

    new_mousebtn_event->__base__            = new_event;
    new_mousebtn_event->__mouse_btn_code__  = mouse_btn_code;
    
    new_mousebtn_event->__debug_str__   = sdscatprintf(sdsempty(), 
                                                        "[%s] Button Code: %d", 
                                                        VampEventTypeToString(type), 
                                                        mouse_btn_code
                                                      );

    new_mousebtn_event->GetButtonCode   = GetButtonCode;
    new_mousebtn_event->GetDebugString  = GetMouseButtonDebugString;

    return new_mousebtn_event;
}


void VampDestroyMouseButtonEvent(VampMouseButtonEvent *event)
{
    sdsfree(event->__debug_str__);
    VAMP_FREE(event);
}






static double GetX(struct VampMousePosEvent *event)
{
    return event->__mouse_x__;
}


static double GetY(struct VampMousePosEvent *event)
{
    return event->__mouse_y__;
}


static const char *GetMousePosDebugString(struct VampMousePosEvent *event)
{
    return event->__debug_str__;
}


static void DeconstructorMousePosEvent(void *event)
{
    VampMousePosEvent *e = (VampMousePosEvent *)event;
    VampDestroyMousePosEvent(e);
}





VampMousePosEvent *VampNewMousePosEvent(VampApplication *app, unsigned int type, double x, double y)
{
    VampEvent *new_event = __VampNewEvent__(app, type);

    VampMousePosEvent *VAMP_MALLOC(new_mousepos_event, sizeof(VampMousePosEvent));


    new_event->__child__                = new_mousepos_event;
    new_event->__ChildDecontructor__    = DeconstructorMousePosEvent;

    new_mousepos_event->__base__            = new_event;
    new_mousepos_event->__mouse_x__         = x;
    new_mousepos_event->__mouse_y__         = y;
    
    new_mousepos_event->__debug_str__   = sdscatprintf(sdsempty(), 
                                                        "[%s] (%f , %f)", 
                                                        VampEventTypeToString(type), 
                                                        x, y
                                                      );

    new_mousepos_event->GetX            = GetX;
    new_mousepos_event->GetY            = GetY;
    new_mousepos_event->GetDebugString  = GetMousePosDebugString;

    return new_mousepos_event;
}


void VampDestroyMousePosEvent(VampMousePosEvent *event)
{
    sdsfree(event->__debug_str__);
    VAMP_FREE(event);
}