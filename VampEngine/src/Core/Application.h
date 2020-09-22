#pragma once
#include <vector>
#include <string>

namespace VampEngine
{
	class Window;
	class Layer;

	class Application
	{

		//Public Methods.
		public:

			//Constructors.
			Application();
			virtual ~Application();

			//Run Method.
			void Run();

			//Push Layer Methods.
			void PushLayer(Layer* layer, const std::string& name = "Layer");
			void PushOverlayer(Layer* overlayer, const std::string& name = "Layer");

			//Inline Methods.
			inline Window& GetWindow() { return *m_window; }


		//Private Members.
		private:

			Window *m_window;

			std::vector<Layer*> m_layers;
			std::vector<Layer*> m_overlayers;


		//Private Methods.
		private:

			void PrepareEvents();

	};


	//Create App Function.
	extern Application* CreateApp();
}