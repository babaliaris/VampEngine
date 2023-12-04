#ifndef SANDBOX_TESTING_EVENTS_LAYER_H
#define SANDBOX_TESTING_EVENTS_LAYER_H
#include <VampEngine.h>

typedef struct TestingEventsLayer
{
    VAMP_LAYER_DECLERATION;
}
TestingEventsLayer;


VampLayer *SandboxNewTestingEventsLayer(const char *debug_name, VampApplication *app);


#endif