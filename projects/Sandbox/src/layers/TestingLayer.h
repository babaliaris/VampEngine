#ifndef SANDBOX_TESTING_LAYER_H
#define SANDBOX_TESTING_LAYER_H

typedef struct VampLayer VampLayer;
typedef struct VampEvent VampEvent;

void TestingLayerOnAttach(VampLayer *layer);
void TestingLayerOnDetach(VampLayer *layer);
void TestingLayerOnUpdate(VampLayer *layer);
void TestingLayerOnEvent(VampLayer *layer, VampEvent *event);

#endif