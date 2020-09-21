#define VAMP_ENTRY
#include <VampEngine.h>


class MyLayer : public VampEngine::Layer
{
	public:

	virtual void OnAttach()
	{
		VAMP_INFO("MyLayer On Attatch!");
	}

	virtual void OnDetatch()
	{
	}

	virtual void OnUpdate()
	{
	}

	virtual void OnEvent(VampEngine::Event& e)
	{
		VampEngine::Dispatcher dispatcher(e);

		dispatcher.Dispatch<VampEngine::WindowResizeEvent>([](VampEngine::WindowResizeEvent& e) -> bool
			{
				VAMP_TRACE(e.ToString().c_str());
				return true;
			});

		dispatcher.Dispatch<VampEngine::WindowMoveEvent>([](VampEngine::WindowMoveEvent& e) -> bool
			{
				VAMP_TRACE(e.ToString().c_str());
				return true;
			});

		dispatcher.Dispatch<VampEngine::WindowFocusEvent>([](VampEngine::WindowFocusEvent& e) -> bool
			{
				VAMP_TRACE(e.ToString().c_str());
				return true;
			});

		dispatcher.Dispatch<VampEngine::WindowLostFocusEvent>([](VampEngine::WindowLostFocusEvent& e) -> bool
			{
				VAMP_TRACE(e.ToString().c_str());
				return true;
			});

		dispatcher.Dispatch<VampEngine::KeyPressEvent>([](VampEngine::KeyPressEvent& e) -> bool
			{
				VAMP_TRACE(e.ToString().c_str());
				return true;
			});

		dispatcher.Dispatch<VampEngine::KeyReleaseEvent>([](VampEngine::KeyReleaseEvent& e) -> bool
			{
				VAMP_TRACE(e.ToString().c_str());
				return true;
			});

		dispatcher.Dispatch<VampEngine::KeyRepeatEvent>([](VampEngine::KeyRepeatEvent& e) -> bool
			{
				VAMP_TRACE(e.ToString().c_str());
				return true;
			});

		dispatcher.Dispatch<VampEngine::MousePressEvent>([](VampEngine::MousePressEvent& e) -> bool
			{
				VAMP_TRACE(e.ToString().c_str());
				return true;
			});

		dispatcher.Dispatch<VampEngine::MouseReleaseEvent>([](VampEngine::MouseReleaseEvent& e) -> bool
			{
				VAMP_TRACE(e.ToString().c_str());
				return true;
			});


		dispatcher.Dispatch<VampEngine::MouseMoveEvent>([](VampEngine::MouseMoveEvent& e) -> bool
			{
				VAMP_TRACE(e.ToString().c_str());
				return true;
			});



		dispatcher.Dispatch<VampEngine::WindowCloseEvent>([](VampEngine::WindowCloseEvent& e) -> bool
			{
				VAMP_TRACE(e.ToString().c_str());
				return true;
			});


		dispatcher.Dispatch<VampEngine::MouseScrollEvent>([](VampEngine::MouseScrollEvent& e) -> bool
			{
				VAMP_TRACE(e.ToString().c_str());
				return true;
			});
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