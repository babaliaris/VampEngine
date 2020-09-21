#pragma once

namespace VampEngine
{
	class Window;

	class Application
	{

		public:
			Application();
			virtual ~Application();

			void Run();

			inline Window& GetWindow() { return *m_window; }

		private:

			Window *m_window;

	};


	extern Application* CreateApp();
}