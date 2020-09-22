#include "pch.h"
#include "Input.h"

//Include GLFWW INPUT.
#if (defined VAMP_WINDOWS || defined VAMP_LINUX || defined VAMP_MACOS)
	#include "Platform/GLFW/GLFWInput.h"
#endif

namespace VampEngine
{
	Input* Input::s_Instance = nullptr;

	//Create GLFW Input.
	#if (defined VAMP_WINDOWS || defined VAMP_LINUX || defined VAMP_MACOS)
		void Input::Create()
		{
			s_Instance = new GLFWInput();
		}
	#endif
}
