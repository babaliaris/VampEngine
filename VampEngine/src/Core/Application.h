#pragma once

namespace VampEngine
{
	class Window;

	class Application
	{

		//Public Methods.
		public:

			//Constructors.
			Application();
			virtual ~Application();

			//Methods.
			void Run();

			//Inline Methods.
			inline Window& GetWindow() { return *m_window; }


		//Private Members.
		private:

			Window *m_window;

	};


	//Create App Function.
	extern Application* CreateApp();
}