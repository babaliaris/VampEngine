#pragma once

#ifdef VAMP_ENTRY

	int main(int argc, char **argv)
	{

		//Create the application.
		VampEngine::Application* app = VampEngine::CreateApp();

		//Run it.
		app->Run();

		//Delete it.
		delete app;

		//Return Successfully!
		return 0;
	}

#endif