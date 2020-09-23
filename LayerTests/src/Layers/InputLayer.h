#pragma once
#include <VampEngine.h>

class InputLayer : public VampEngine::Layer
{
	public:
		InputLayer();

		virtual ~InputLayer();

		virtual void OnAttach() override;

		virtual void OnDetatch() override;

		virtual void OnUpdate() override;

		virtual void OnEvent(VampEngine::Event& e) override;

	private:
		VampEngine::Input* m_Input;
};

