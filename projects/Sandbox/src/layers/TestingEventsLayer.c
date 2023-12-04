#include "TestingEventsLayer.h"


static char HandleKeyPressedEvent(void *event, void *layer)
{
    VampKeyboardEvent *e = (VampKeyboardEvent *)event;

    VAMP_INFO(e->GetDebugString(e));

    return 0;
}


static char HandleMouseButtonPressedEvent(void *event, void *layer)
{
    VampMouseButtonEvent *e = (VampMouseButtonEvent *)event;

    VAMP_INFO(e->GetDebugString(e));

    return 0;
}


static char HandleMouseButtonReleasedEvent(void *event, void *layer)
{
    VampMouseButtonEvent *e = (VampMouseButtonEvent *)event;

    VAMP_INFO(e->GetDebugString(e));

    return 0;
}


static char HandleMousePosEvent(void *event, void *layer)
{
    VampMousePosEvent *e = (VampMousePosEvent *)event;

    VAMP_INFO(e->GetDebugString(e));

    return 0;
}


static char HandleWindowFocusedEvent(void *event, void *layer)
{
    VampWindowEvent *e = (VampWindowEvent *)event;

    VAMP_INFO(e->GetDebugString(e));

    return 0;
}


static char HandleWindowLostFocusEvent(void *event, void *layer)
{
    VampWindowEvent *e = (VampWindowEvent *)event;

    VAMP_INFO(e->GetDebugString(e));

    return 0;
}


static char HandleWindowMaximizedEvent(void *event, void *layer)
{
    VampWindowEvent *e = (VampWindowEvent *)event;

    VAMP_INFO(e->GetDebugString(e));

    return 0;
}


static char HandleWindowMinimizedEvent(void *event, void *layer)
{
    VampWindowEvent *e = (VampWindowEvent *)event;

    VAMP_INFO(e->GetDebugString(e));

    return 0;
}


static char HandleWindowRestoredEvent(void *event, void *layer)
{
    VampWindowEvent *e = (VampWindowEvent *)event;

    VAMP_INFO(e->GetDebugString(e));

    return 0;
}


static char HandleWindowMovedEvent(void *event, void *layer)
{
    VampWindowMovedEvent *e = (VampWindowMovedEvent *)event;

    VAMP_INFO(e->GetDebugString(e));

    return 0;
}


static char HandleWindowResizedEvent(void *event, void *layer)
{
    VampWindowResizedEvent *e = (VampWindowResizedEvent *)event;

    VAMP_INFO(e->GetDebugString(e));

    return 0;
}










static void OnAttach(void *layer)
{
    TestingEventsLayer *l = (TestingEventsLayer *)layer;
    VAMP_CLIENT_INFO("[%s] OnAttach()", l->debug_name);
}


static void OnDetach(void *layer)
{
}


static void OnUpdate(void *layer)
{
}


static void OnEvent(void *layer, VampEvent *event)
{
    event->Dispatch(event, VAMP_EVENT_KEY_PRESSED, HandleKeyPressedEvent, layer);
    event->Dispatch(event, VAMP_EVENT_MOUSE_PRESSED, HandleMouseButtonPressedEvent, layer);
    event->Dispatch(event, VAMP_EVENT_MOUSE_RELEASED, HandleMouseButtonReleasedEvent, layer);
    event->Dispatch(event, VAMP_EVENT_MOUSE_POS, HandleMousePosEvent, layer);
    event->Dispatch(event, VAMP_EVENT_WINDOW_FOCUSED, HandleWindowFocusedEvent, layer);
    event->Dispatch(event, VAMP_EVENT_WINDOW_LOST_FOCUS, HandleWindowLostFocusEvent, layer);
    event->Dispatch(event, VAMP_EVENT_WINDOW_MAXIMIZED, HandleWindowMaximizedEvent, layer);
    event->Dispatch(event, VAMP_EVENT_WINDOW_MINIMIZED, HandleWindowMinimizedEvent, layer);
    event->Dispatch(event, VAMP_EVENT_WINDOW_RESTORED, HandleWindowRestoredEvent, layer);
    event->Dispatch(event, VAMP_EVENT_WINDOW_MOVED, HandleWindowMovedEvent, layer);
    event->Dispatch(event, VAMP_EVENT_WINDOW_RESIZED, HandleWindowResizedEvent, layer);
}


static void Deconstructor(void *layer)
{   
    TestingEventsLayer *l = (TestingEventsLayer *)layer;
    sdsfree(l->debug_name);
    VAMP_FREE(l);
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