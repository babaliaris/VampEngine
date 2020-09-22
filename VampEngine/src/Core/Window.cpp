#include "pch.h"
#include "Window.h"

//Include GLFWWindow.
#if (defined VAMP_WINDOWS || defined VAMP_LINUX || defined VAMP_MACOS)
	#include "Platform/GLFW/GFLWWindow.h"
#endif

namespace VampEngine
{

	//GLFW WINDOW.
	#if (defined VAMP_WINDOWS || defined VAMP_LINUX || defined VAMP_MACOS)
		Window* Window::Create(int width, int height, const std::string& title)
		{
			return new GLFWWindow(width, height, title);
		}
	#endif
}