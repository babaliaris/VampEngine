#pragma once
#include <string>
#include <functional>
#include "Events/Event.h"

struct GLFWwindow;

namespace VampEngine
{
	class Window
	{

		//Public Methods.
		public:

			friend class Application;

			//Constructors.
			Window(int width = 800, int height = 600, const std::string& title = "VampEngine");
			~Window();

			//Methods.
			void Update();

			//Inline Methods.
			inline unsigned int GetWidth() const { return m_data.width; }
			inline unsigned int GetHeight() const { return m_data.height; }

			inline int GetX() const { return m_data.x; }
			inline int GetY() const { return m_data.y; }

			inline const std::string& GetTitle() const { return m_data.title; }

			inline bool IsMinimized() const { return m_data.minimized; }
			inline bool IsMaximized() const { return m_data.maximized; }



		//Private Methods.
		private:

			void Init();

			void ConnectEventSystem();


		//Private Members.
		private:

			struct WindowData
			{
				using EventCallback = std::function<void(Event&)>;

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

