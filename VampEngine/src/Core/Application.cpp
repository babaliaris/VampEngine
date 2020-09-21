#include "Application.h"
#include "Window.h"

namespace VampEngine
{
	Application::Application()
		: m_window(new Window())
	{
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