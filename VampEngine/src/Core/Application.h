#pragma once
#include <vector>

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
			void PushLayer(Layer* layer);
			void PushOverlayer(Layer* layer);

			//Inline Methods.
			inline Window& GetWindow() { return *m_window; }


		//Private Members.
		private:

			Window *m_window;

			std::vector<Layer*> m_layers;
			std::vector<Layer*> m_overlayers;

	};


	//Create App Function.
	extern Application* CreateApp();
}