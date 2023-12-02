#include "TestingLayer.h"
#include <VampEngine.h>

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
    VAMP_CLIENT_INFO("[%s] OnUpdate()", layer->GetDebugName(layer));
}