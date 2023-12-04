#include "TestingLayer.h"
#include <VampEngine.h>


char HandleKeyPressedEvent(void *event)
{
    VampKeyboardEvent *e = (VampKeyboardEvent *)event;

    VAMP_INFO(e->GetDebugString(e));

    return 0;
}


char HandleMouseButtonPressedEvent(void *event)
{
    VampMouseButtonEvent *e = (VampMouseButtonEvent *)event;

    VAMP_INFO(e->GetDebugString(e));

    return 0;
}


char HandleMouseButtonReleasedEvent(void *event)
{
    VampMouseButtonEvent *e = (VampMouseButtonEvent *)event;

    VAMP_INFO(e->GetDebugString(e));

    return 0;
}


char HandleMousePosEvent(void *event)
{
    VampMousePosEvent *e = (VampMousePosEvent *)event;

    VAMP_INFO(e->GetDebugString(e));

    return 0;
}


char HandleWindowFocusedEvent(void *event)
{
    VampWindowEvent *e = (VampWindowEvent *)event;

    VAMP_INFO(e->GetDebugString(e));

    return 0;
}


char HandleWindowLostFocusEvent(void *event)
{
    VampWindowEvent *e = (VampWindowEvent *)event;

    VAMP_INFO(e->GetDebugString(e));

    return 0;
}


char HandleWindowMaximizedEvent(void *event)
{
    VampWindowEvent *e = (VampWindowEvent *)event;

    VAMP_INFO(e->GetDebugString(e));

    return 0;
}


char HandleWindowMinimizedEvent(void *event)
{
    VampWindowEvent *e = (VampWindowEvent *)event;

    VAMP_INFO(e->GetDebugString(e));

    return 0;
}


char HandleWindowRestoredEvent(void *event)
{
    VampWindowEvent *e = (VampWindowEvent *)event;

    VAMP_INFO(e->GetDebugString(e));

    return 0;
}


char HandleWindowMovedEvent(void *event)
{
    VampWindowMovedEvent *e = (VampWindowMovedEvent *)event;

    VAMP_INFO(e->GetDebugString(e));

    return 0;
}


char HandleWindowResizedEvent(void *event)
{
    VampWindowResizedEvent *e = (VampWindowResizedEvent *)event;

    VAMP_INFO(e->GetDebugString(e));

    return 0;
}










void TestingLayerOnAttach(VampLayer *layer)
{
    VAMP_CLIENT_INFO("[%s] OnAttach()", layer->GetDebugName(layer));
}


void TestingLayerOnDetach(VampLayer *layer)
{
    VAMP_CLIENT_INFO("[%s] OnDetach()", layer->GetDebugName(layer));
}


void TestingLayerOnUpdate(VampLayer *layer)
{
}

void TestingLayerOnEvent(VampLayer *layer, VampEvent *event)
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