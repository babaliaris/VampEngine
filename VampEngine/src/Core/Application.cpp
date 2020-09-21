#include "pch.h"
#include "Application.h"
#include "Window.h"
#include "Layer.h"
#include "Events/WindowEvents.h"
#include "Events/KeyEvents.h"
#include "Events/MouseEvents.h"


namespace VampEngine
{
	Application::Application()
		: m_window(new Window())
	{
		this->PrepareEvents();
	}



	Application::~Application()
	{
	}



	void Application::Run()
	{
		while (true)
		{

			//If the Window is not minimized, run the Layers.
			if (!m_window->IsMinimized())
			{

				//Run Layers.
				for (Layer* layer : m_layers)
				{
					if (layer->active)
						layer->OnUpdate();
				}

				//Run Overlayers.
				for (Layer* overlayer : m_overlayers)
				{
					if (overlayer->active)
						overlayer->OnUpdate();
				}
			}

			//Update the Window.
			m_window->Update();
		}
	}




	void Application::PushLayer(Layer* layer)
	{
		m_layers.push_back(layer);
		layer->OnAttach();
	}




	void Application::PushOverlayer(Layer* layer)
	{
		m_overlayers.push_back(layer);
		layer->OnAttach();
	}





	void Application::PrepareEvents()
	{
		//Set the Event Callback Method.
		m_window->m_data.callback = [this](Event& e)->void
		{
			//Run Layers OnEvent Backwards.
			for (std::vector<Layer *>::reverse_iterator it = m_layers.rbegin(); it != m_layers.rend(); it++)
			{
				if ( (*it)->active )
					(*it)->OnEvent(e);
			}

			//Run Layers OnEvent Backwards.
			for (std::vector<Layer*>::reverse_iterator it = m_overlayers.rbegin(); it != m_overlayers.rend(); it++)
			{
				if ((*it)->active)
					(*it)->OnEvent(e);
			}
		};
	}
}