#define VAMP_ENTRY
#include <VampEngine.h>

#include "Layers/EventsLayer.h"


class LayerTests : public VampEngine::Application
{

public:

	LayerTests()
	{
		PushLayer(new EventsLayer(), "EventsLayer");
	}

	~LayerTests()
	{
	}
};

VampEngine::Application* VampEngine::CreateApp()
{
	return new LayerTests();
}