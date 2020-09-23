#include "pch.h"
#include "Application.h"
#include "Window.h"
#include "Input/Input.h"
#include "Layer.h"
#include "Events/WindowEvents.h"
#include "Events/KeyEvents.h"
#include "Events/MouseEvents.h"
#include "FileSystem.h"
#include "Renderer/RendererCommand.h"


namespace VampEngine
{

	Application* Application::s_Instance = nullptr;


	Application::Application()
		: m_window(Window::Create())
	{
		//Set the instance.
		VAMP_ASSERT(s_Instance == nullptr, "s_Instance should be null at this point!");
		s_Instance = this;

		//Create The Input Instance.
		Input::Create();

		//Create The File System.
		FileSystem::Create();

		//Create The Renderer Command.
		RendererCommand::Create();

		//Prepare The Events.
		this->PrepareEvents();
	}



	Application::~Application()
	{

		//Delete all layers.
		for (Layer* layer : m_layers)
			delete layer;

		//Delete all overlayers.
		for (Layer* overlayer : m_overlayers)
			delete overlayer;

		//Delete Input Static Varaible.
		delete Input::Get();

		//Delete the file system instance.
		delete FileSystem::Get();

		//Delete the Renderer command.
		delete RendererCommand::Get();

		//Delete the window.
		delete m_window;
	}



	void Application::Run()
	{

		//Set Clear Color To Black.
		RendererCommand::Get()->SetClearColor({ 0.0f, 0.0f, 0.0f, 1.0f });

		while (true)
		{

			//Clear The Screen.
			RendererCommand::Get()->Clear();

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


			//Update the Inputs.
			Input::Get()->OnUpdate();

			//Update the Window.
			m_window->Update();
		}
	}




	void Application::PushLayer(Layer* layer, const std::string& name)
	{
		layer->name = name;
		m_layers.push_back(layer);
		layer->OnAttach();
	}




	void Application::PushOverlayer(Layer* overlayer, const std::string& name)
	{

		overlayer->name = name;
		m_overlayers.push_back(overlayer);
		overlayer->OnAttach();
	}





	void Application::PrepareEvents()
	{
		//Set the Event Callback Method.
		m_window->GetEventCallback() = [this](Event& e)->void
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