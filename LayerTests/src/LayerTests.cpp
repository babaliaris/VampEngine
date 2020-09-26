#define VAMP_ENTRY
#include <VampEngine.h>

#include "Layers/EventsLayer.h"
#include "Layers/InputLayer.h"
#include "Layers/BufferLayer.h"
#include "Layers/TextureLayer.h"


class LayerTests : public VampEngine::Application
{

public:

	LayerTests()
	{
		//PushLayer(new EventsLayer(), "EventsLayer");
		//PushLayer(new InputLayer(), "InputLayer");
		//PushLayer(new BufferLayer(), "BufferLayer");
		PushLayer(new TextureLayer(), "TextureLayer");
	}

	~LayerTests()
	{
	}
};

VampEngine::Application* VampEngine::CreateApp()
{
	return new LayerTests();
}