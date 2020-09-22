#include "InputLayer.h"

InputLayer::InputLayer()
	: m_Input(VampEngine::Input::Get())
{
}



InputLayer::~InputLayer()
{
}



void InputLayer::OnAttach()
{
}



void InputLayer::OnDetatch()
{
}



void InputLayer::OnUpdate()
{
	if (m_Input.KeyDown(VAMP_KEY_W))
	{
		VAMP_TRACE("W IS BEING PRESSED!");
	}

	/*
	if (m_Input.KeyUp(VAMP_KEY_W))
	{
		VAMP_TRACE("W IS BEING RELEASED!");
	}
	*/


	if (m_Input.MouseButtonDown(VAMP_MOUSE_BUTTON_1))
	{
		VAMP_TRACE("LEFT MOUSE BUTTON DOWN!");
	}

	/*
	if (m_Input.MouseButtonUp(VAMP_MOUSE_BUTTON_1))
	{
		VAMP_TRACE("LEFT MOUSE BUTTON UP!");
	}
	*/

	if (m_Input.GetMouseScroll())
	{
		VAMP_TRACE("Mouse Scroll Amount: %.3f", m_Input.GetMouseScroll());
	}

	/*
	VAMP_TRACE("Mouse x: %.3f , Mouse y: %.3f", m_Input.GetMouseX(), m_Input.GetMouseY());
	*/


}



void InputLayer::OnEvent(VampEngine::Event& e)
{
}
