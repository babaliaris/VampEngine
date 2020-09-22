#pragma once
#include "Core/Window.h"

struct GLFWwindow;

namespace VampEngine
{
	class GLFWWindow : public Window
	{
		//Event Callback Method Signature.
		using EventCallback = std::function<void(Event&)>;

		//Public Methods.
		public:

			friend class Application;

			//Constructors.
			GLFWWindow(int width = 800, int height = 600, const std::string& title = "VampEngine");
			~GLFWWindow();

			//Methods.
			virtual void Update() const override;

			//Get Width And Height.
			virtual inline unsigned int GetWidth() const override { return m_data.width; }
			virtual inline unsigned int GetHeight() const override  { return m_data.height; }

			//Get X, Y, Window Coordinates.
			virtual inline int GetX() const override { return m_data.x; }
			virtual inline int GetY() const override { return m_data.y; }

			//Get Window Title.
			virtual inline const std::string& GetTitle() const override { return m_data.title; }

			//Get Event Callback.
			virtual inline EventCallback& GetEventCallback() override { return m_data.callback; };

			//Check if minimized or maximized.
			virtual inline bool IsMinimized() const override { return m_data.minimized; };
			virtual inline bool IsMaximized() const override { return m_data.maximized; };

			//Get Native Window.
			virtual inline void* GetNativeWindow() override { return (void *)m_glfwWindow; };



		//Private Methods.
		private:

			void Init();

			void ConnectEventSystem();


		//Private Members.
		private:

			//Window Data Structure.
			struct WindowData
			{

				unsigned int	width;
				unsigned int	height;
				int				x;
				int				y;
				std::string		title;
				EventCallback	callback;
				bool			minimized = false;
				bool			maximized = false;

				WindowData(int w, int h, const std::string& t)
					: width(w), height(h), x(0), y(0), title(t), callback(nullptr)
				{}
			};

			WindowData	m_data;
			GLFWwindow* m_glfwWindow;
	};
}

