#include "pch.h"
#include "Application.h"
#include "Window.h"

#include "Events/WindowEvents.h"
#include "Events/KeyEvents.h"
#include "Events/MouseEvents.h"

namespace VampEngine
{
	Application::Application()
		: m_window(new Window())
	{
		//WindowResizeEvent e(1024, 608);
		//WindowMoveEvent e;
		//WindowFocusEvent e;
		//WindowLostFocusEvent e;
		//KeyPressEvent e(12);
		//KeyReleaseEvent e(13);
		//KeyRepeatEvent e(14, 6);
		//MousePressEvent e(0);
		//MouseReleaseEvent e(1);
		MouseMoveEvent e(100.4510, 200.45144);

		Dispatcher dispatcher(e);

		dispatcher.Dispatch<WindowResizeEvent>([](WindowResizeEvent& e) -> bool
		{
				VAMP_TRACE(e.ToString().c_str());
				return true;
		});

		dispatcher.Dispatch<WindowMoveEvent>([](WindowMoveEvent& e) -> bool
		{
			VAMP_TRACE(e.ToString().c_str());
			return true;
		});

		dispatcher.Dispatch<WindowFocusEvent>([](WindowFocusEvent& e) -> bool
		{
			VAMP_TRACE(e.ToString().c_str());
			return true;
		});

		dispatcher.Dispatch<WindowLostFocusEvent>([](WindowLostFocusEvent& e) -> bool
		{
			VAMP_TRACE(e.ToString().c_str());
			return true;
		});

		dispatcher.Dispatch<KeyPressEvent>([](KeyPressEvent& e) -> bool
		{
			VAMP_TRACE(e.ToString().c_str());
			return true;
		});

		dispatcher.Dispatch<KeyReleaseEvent>([](KeyReleaseEvent& e) -> bool
		{
			VAMP_TRACE(e.ToString().c_str());
			return true;
		});

		dispatcher.Dispatch<KeyRepeatEvent>([](KeyRepeatEvent& e) -> bool
		{
			VAMP_TRACE(e.ToString().c_str());
			return true;
		});

		dispatcher.Dispatch<MousePressEvent>([](MousePressEvent& e) -> bool
		{
			VAMP_TRACE(e.ToString().c_str());
			return true;
		});

		dispatcher.Dispatch<MouseReleaseEvent>([](MouseReleaseEvent& e) -> bool
		{
			VAMP_TRACE(e.ToString().c_str());
			return true;
		});


		dispatcher.Dispatch<MouseMoveEvent>([](MouseMoveEvent& e) -> bool
		{
			VAMP_TRACE(e.ToString().c_str());
			return true;
		});
	}



	Application::~Application()
	{
	}



	void Application::Run()
	{
		while (true)
		{
			m_window->Update();
		}
	}
}