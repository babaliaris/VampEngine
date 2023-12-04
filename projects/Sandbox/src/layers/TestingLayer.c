#include "TestingLayer.h"
#include <VampEngine.h>


char HandleKeyPressedEvent(void *event)
{
    VampKeyboardEvent *e = (VampKeyboardEvent *)event;

    VAMP_INFO("[%s:%d]", VampEventTypeToString(e->__base__->__type__), e->__keycode__);

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
}