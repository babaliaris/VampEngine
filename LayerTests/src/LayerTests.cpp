#define VAMP_ENTRY
#include <VampEngine.h>

#include "Layers/EventsLayer.h"
#include "Layers/InputLayer.h"


class LayerTests : public VampEngine::Application
{

public:

	LayerTests()
	{
		//PushLayer(new EventsLayer(), "EventsLayer");
		PushLayer(new InputLayer(), "InputLayer");
	}

	~LayerTests()
	{
	}
};

VampEngine::Application* VampEngine::CreateApp()
{
	return new LayerTests();
}