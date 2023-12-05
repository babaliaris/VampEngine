#include "TestingEventsLayer.h"


static char HandleKeyPressedEvent(void *event, void *this)
{
    VampKeyboardEvent *e = (VampKeyboardEvent *)event;

    VAMP_INFO(e->GetDebugString(e));

    return 0;
}


static char HandleMouseButtonPressedEvent(void *event, void *this)
{
    VampMouseButtonEvent *e = (VampMouseButtonEvent *)event;

    VAMP_INFO(e->GetDebugString(e));

    return 0;
}


static char HandleMouseButtonReleasedEvent(void *event, void *this)
{
    VampMouseButtonEvent *e = (VampMouseButtonEvent *)event;

    VAMP_INFO(e->GetDebugString(e));

    return 0;
}


static char HandleMousePosEvent(void *event, void *this)
{
    VampMousePosEvent *e = (VampMousePosEvent *)event;

    VAMP_INFO(e->GetDebugString(e));

    return 0;
}


static char HandleWindowFocusedEvent(void *event, void *this)
{
    VampWindowEvent *e = (VampWindowEvent *)event;

    VAMP_INFO(e->GetDebugString(e));

    return 0;
}


static char HandleWindowLostFocusEvent(void *event, void *this)
{
    VampWindowEvent *e = (VampWindowEvent *)event;

    VAMP_INFO(e->GetDebugString(e));

    return 0;
}


static char HandleWindowMaximizedEvent(void *event, void *this)
{
    VampWindowEvent *e = (VampWindowEvent *)event;

    VAMP_INFO(e->GetDebugString(e));

    return 0;
}


static char HandleWindowMinimizedEvent(void *event, void *this)
{
    VampWindowEvent *e = (VampWindowEvent *)event;

    VAMP_INFO(e->GetDebugString(e));

    return 0;
}


static char HandleWindowRestoredEvent(void *event, void *this)
{
    VampWindowEvent *e = (VampWindowEvent *)event;

    VAMP_INFO(e->GetDebugString(e));

    return 0;
}


static char HandleWindowMovedEvent(void *event, void *this)
{
    VampWindowMovedEvent *e = (VampWindowMovedEvent *)event;

    VAMP_INFO(e->GetDebugString(e));

    return 0;
}


static char HandleWindowResizedEvent(void *event, void *this)
{
    VampWindowResizedEvent *e = (VampWindowResizedEvent *)event;

    VAMP_INFO(e->GetDebugString(e));

    return 0;
}










static void OnAttach(void *this)
{
    TestingEventsLayer *t = (TestingEventsLayer *)this;
    VAMP_CLIENT_INFO("[%s] OnAttach()", t->debug_name);
}


static void OnDetach(void *this)
{
}


static void OnUpdate(void *this)
{
}


static void OnEvent(void *this, VampEvent *event)
{
    event->Dispatch(event, VAMP_EVENT_KEY_PRESSED, HandleKeyPressedEvent, this);
    event->Dispatch(event, VAMP_EVENT_MOUSE_PRESSED, HandleMouseButtonPressedEvent, this);
    event->Dispatch(event, VAMP_EVENT_MOUSE_RELEASED, HandleMouseButtonReleasedEvent, this);
    event->Dispatch(event, VAMP_EVENT_MOUSE_POS, HandleMousePosEvent, this);
    event->Dispatch(event, VAMP_EVENT_WINDOW_FOCUSED, HandleWindowFocusedEvent, this);
    event->Dispatch(event, VAMP_EVENT_WINDOW_LOST_FOCUS, HandleWindowLostFocusEvent, this);
    event->Dispatch(event, VAMP_EVENT_WINDOW_MAXIMIZED, HandleWindowMaximizedEvent, this);
    event->Dispatch(event, VAMP_EVENT_WINDOW_MINIMIZED, HandleWindowMinimizedEvent, this);
    event->Dispatch(event, VAMP_EVENT_WINDOW_RESTORED, HandleWindowRestoredEvent, this);
    event->Dispatch(event, VAMP_EVENT_WINDOW_MOVED, HandleWindowMovedEvent, this);
    event->Dispatch(event, VAMP_EVENT_WINDOW_RESIZED, HandleWindowResizedEvent, this);
}


static void Deconstructor(void *this)
{   
    TestingEventsLayer *t = (TestingEventsLayer *)this;
    sdsfree(t->debug_name);
    VAMP_FREE(t);
}



VampLayer *SandboxNewTestingEventsLayer(VampApplication *app)
{
    TestingEventsLayer *VAMP_MALLOC(testing_events_layer, sizeof(TestingEventsLayer));
    testing_events_layer->debug_name = sdsnew("Testing Events Layer");

    VAMP_LAYER_IMPLEMENTATION(testing_events_layer,
                              app,
                              OnAttach,
                              OnDetach,
                              OnUpdate,
                              OnEvent);
}