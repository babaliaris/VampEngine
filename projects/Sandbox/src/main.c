#define VAMP_ENGINE_ENTRY_POINT
#include <VampEngine.h>

#include <layers/TestingLayer.h>

void Sandbox(VampApplication *app)
{
    /*
    VampLayer *testing_layer = VampNewLayer("Testing Layer",
                                            app,
                                            TestingLayerOnAttach, 
                                            TestingLayerOnDetach, 
                                            TestingLayerOnUpdate);

    app->AppendLayer(app, testing_layer);
    */
}

VampApplication *VampCreateUserApplication()
{
    return VampNewApplication(Sandbox, "Sandbox", 800, 600);
}
