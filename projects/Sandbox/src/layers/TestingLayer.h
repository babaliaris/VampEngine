#ifndef SANDBOX_TESTING_LAYER_H
#define SANDBOX_TESTING_LAYER_H

typedef struct VampLayer VampLayer;

void TestingLayerOnAttach(VampLayer *layer);
void TestingLayerOnDetach(VampLayer *layer);
void TestingLayerOnUpdate(VampLayer *layer);

#endif