#pragma once
#include <VampEngine.h>

class BufferLayer : public VampEngine::Layer
{
	public:
		BufferLayer();

		virtual ~BufferLayer();

		virtual void OnAttach() override;

		virtual void OnDetatch() override;

		virtual void OnUpdate() override;

		virtual void OnEvent(VampEngine::Event& e) override;
};

