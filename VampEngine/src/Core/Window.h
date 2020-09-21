#pragma once
#include <string>

struct GLFWwindow;

namespace VampEngine
{
	class Window
	{
		public:

			Window(int width = 800, int height = 600, const std::string& title = "VampEngine");
			~Window();

			void Update();

			inline int GetWidth() const { return m_data.width; }
			inline int GetHeight() const { return m_data.height; }
			inline const std::string& GetTitle() const { return m_data.title; }

		private:

			void Init();


		private:

			struct WindowData
			{
				int			width;
				int			height;
				std::string title;

				WindowData(int w, int h, const std::string& t)
					: width(w), height(h), title(t)
				{}
			};

			WindowData	m_data;
			GLFWwindow* m_glfwWindow;
	};
}

