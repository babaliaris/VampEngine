#define VAMP_ENTRY
#include <VampEngine.h>

class MyApp : public VampEngine::Application
{

	public:

		MyApp(){}
		~MyApp(){}

	private:

};

VampEngine::Application* VampEngine::CreateApp()
{
	VAMP_INFO("APP created!");
	return new MyApp();
}