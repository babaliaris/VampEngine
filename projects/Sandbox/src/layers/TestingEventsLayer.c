#include "TestingEventsLayer.h"


static char HandleKeyPressedEvent(void *event)
{
    VampKeyboardEvent *e = (VampKeyboardEvent *)event;

    VAMP_INFO(e->GetDebugString(e));

    return 0;
}


static char HandleMouseButtonPressedEvent(void *event)
{
    VampMouseButtonEvent *e = (VampMouseButtonEvent *)event;

    VAMP_INFO(e->GetDebugString(e));

    return 0;
}


static char HandleMouseButtonReleasedEvent(void *event)
{
    VampMouseButtonEvent *e = (VampMouseButtonEvent *)event;

    VAMP_INFO(e->GetDebugString(e));

    return 0;
}


static char HandleMousePosEvent(void *event)
{
    VampMousePosEvent *e = (VampMousePosEvent *)event;

    VAMP_INFO(e->GetDebugString(e));

    return 0;
}


static char HandleWindowFocusedEvent(void *event)
{
    VampWindowEvent *e = (VampWindowEvent *)event;

    VAMP_INFO(e->GetDebugString(e));

    return 0;
}


static char HandleWindowLostFocusEvent(void *event)
{
    VampWindowEvent *e = (VampWindowEvent *)event;

    VAMP_INFO(e->GetDebugString(e));

    return 0;
}


static char HandleWindowMaximizedEvent(void *event)
{
    VampWindowEvent *e = (VampWindowEvent *)event;

    VAMP_INFO(e->GetDebugString(e));

    return 0;
}


static char HandleWindowMinimizedEvent(void *event)
{
    VampWindowEvent *e = (VampWindowEvent *)event;

    VAMP_INFO(e->GetDebugString(e));

    return 0;
}


static char HandleWindowRestoredEvent(void *event)
{
    VampWindowEvent *e = (VampWindowEvent *)event;

    VAMP_INFO(e->GetDebugString(e));

    return 0;
}


static char HandleWindowMovedEvent(void *event)
{
    VampWindowMovedEvent *e = (VampWindowMovedEvent *)event;

    VAMP_INFO(e->GetDebugString(e));

    return 0;
}


static char HandleWindowResizedEvent(void *event)
{
    VampWindowResizedEvent *e = (VampWindowResizedEvent *)event;

    VAMP_INFO(e->GetDebugString(e));

    return 0;
}










static void OnAttach(VampLayer *layer)
{
    VAMP_CLIENT_INFO("[%s] OnAttach()", layer->GetDebugName(layer));
}


static void OnDetach(VampLayer *layer)
{
    VAMP_CLIENT_INFO("[%s] OnDetach()", layer->GetDebugName(layer));
}


static void OnUpdate(VampLayer *layer)
{
}


static void OnEvent(VampLayer *layer, VampEvent *event)
{
    event->Dispatch(event, VAMP_EVENT_KEY_PRESSED, HandleKeyPressedEvent);
    event->Dispatch(event, VAMP_EVENT_MOUSE_PRESSED, HandleMouseButtonPressedEvent);
    event->Dispatch(event, VAMP_EVENT_MOUSE_RELEASED, HandleMouseButtonReleasedEvent);
    event->Dispatch(event, VAMP_EVENT_MOUSE_POS, HandleMousePosEvent);
    event->Dispatch(event, VAMP_EVENT_WINDOW_FOCUSED, HandleWindowFocusedEvent);
    event->Dispatch(event, VAMP_EVENT_WINDOW_LOST_FOCUS, HandleWindowLostFocusEvent);
    event->Dispatch(event, VAMP_EVENT_WINDOW_MAXIMIZED, HandleWindowMaximizedEvent);
    event->Dispatch(event, VAMP_EVENT_WINDOW_MINIMIZED, HandleWindowMinimizedEvent);
    event->Dispatch(event, VAMP_EVENT_WINDOW_RESTORED, HandleWindowRestoredEvent);
    event->Dispatch(event, VAMP_EVENT_WINDOW_MOVED, HandleWindowMovedEvent);
    event->Dispatch(event, VAMP_EVENT_WINDOW_RESIZED, HandleWindowResizedEvent);
}


static void Deconstructor(void *layer)
{   
    TestingEventsLayer *l = (TestingEventsLayer *)layer;
    VAMP_FREE(l);
}



VampLayer *SandboxNewTestingEventsLayer(const char *debug_name, VampApplication *app)
{
    TestingEventsLayer *VAMP_MALLOC(testing_events_layer, sizeof(TestingEventsLayer));

    VAMP_LAYER_IMPLEMENTATION(testing_events_layer,
                              app,
                              debug_name,
                              OnAttach,
                              OnDetach,
                              OnUpdate,
                              OnEvent);
}