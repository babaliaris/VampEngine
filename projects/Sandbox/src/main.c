#define VAMP_ENGINE_ENTRY_POINT
#include <VampEngine.h>

#include <layers/TestingEventsLayer.h>

void Sandbox(VampApplication *app)
{
    /*
    VampLayer *testing_layer = SandboxNewTestingEventsLayer(app);

    app->AppendLayer(app, testing_layer);
    */
    
}

VampApplication *VampCreateUserApplication()
{
    return VampNewApplication(Sandbox, "Sandbox", 800, 600);
}
