#pragma once
#include <VampEngine.h>

class EventsLayer : public VampEngine::Layer
{

	public:
		virtual void OnAttach() override;

		virtual void OnDetatch() override;

		virtual void OnUpdate() override;

		virtual void OnEvent(VampEngine::Event& e) override;
};

