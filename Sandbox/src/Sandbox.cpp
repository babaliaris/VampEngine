#define VAMP_ENTRY
#include <VampEngine.h>


class MyLayer : public VampEngine::Layer
{
	public:

	virtual void OnAttach()
	{
		VAMP_INFO("MyLayer On Attatch!");
		this->active = false;
	}

	virtual void OnDetatch()
	{
	}

	virtual void OnUpdate()
	{
		VAMP_INFO("MyLayer On Update!");
	}

	virtual void OnEvent(VampEngine::Event& e)
	{
	}
};


class MyApp : public VampEngine::Application
{

	public:

		MyApp()
		{
			PushLayer(new MyLayer());
		}

		~MyApp(){}

	private:

};

VampEngine::Application* VampEngine::CreateApp()
{
	VAMP_INFO("APP created!");
	return new MyApp();
}