#ifndef SANDBOX_TESTING_EVENTS_LAYER_H
#define SANDBOX_TESTING_EVENTS_LAYER_H
#include <VampEngine.h>

typedef struct TestingEventsLayer
{
    VAMP_LAYER_DECLERATION;
    char *debug_name;
}
TestingEventsLayer;


VampLayer *SandboxNewTestingEventsLayer(VampApplication *app);


#endif