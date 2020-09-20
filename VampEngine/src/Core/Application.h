#pragma once

namespace VampEngine
{
	class Application
	{

		public:
			Application();
			virtual ~Application();

			void Run();

		private:

	};


	extern Application* CreateApp();
}