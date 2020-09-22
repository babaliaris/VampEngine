#include "pch.h"
#include "GLFWInput.h"
#include "Core/Application.h"
#include "Core/Window.h"
#include <GLFW/glfw3.h>

namespace VampEngine
{

	double GLFWInput::s_ScrollX = 0;
	double GLFWInput::s_ScrollY = 0;


	GLFWInput::GLFWInput()
	{
		Application& app = Application::Get();
		GLFWwindow* window = static_cast<GLFWwindow*>(app.GetWindow().GetNativeWindow());

		//Set Scroll Callback.
		glfwSetScrollCallback(window, [](GLFWwindow* window, double x, double y)
		{
				s_ScrollX = x;
				s_ScrollY = y;
		});
	}



	GLFWInput::~GLFWInput()
	{
	}



	bool GLFWInput::KeyDown(unsigned int keycode)
	{
		Application& app	= Application::Get();
		GLFWwindow* window	= static_cast<GLFWwindow *>(app.GetWindow().GetNativeWindow());

		//Keycode is pressed.
		if (glfwGetKey(window, keycode) == GLFW_PRESS)
			return true;

		return false;
	}



	bool GLFWInput::KeyUp(unsigned int keycode)
	{
		Application& app = Application::Get();
		GLFWwindow* window = static_cast<GLFWwindow*>(app.GetWindow().GetNativeWindow());

		//Keycode is released.
		if (glfwGetKey(window, keycode) == GLFW_RELEASE)
			return true;

		return false;
	}



	bool GLFWInput::KeyDownOnce(unsigned int keycode)
	{
		return false;
	}



	bool GLFWInput::MouseButtonDown(unsigned int button)
	{
		Application& app = Application::Get();
		GLFWwindow* window = static_cast<GLFWwindow*>(app.GetWindow().GetNativeWindow());

		//Button is Pressed.
		if (glfwGetMouseButton(window, button) == GLFW_PRESS)
			return true;

		return false;
	}



	bool GLFWInput::MouseButtonUp(unsigned int button)
	{
		Application& app = Application::Get();
		GLFWwindow* window = static_cast<GLFWwindow*>(app.GetWindow().GetNativeWindow());

		//Button is Released.
		if (glfwGetMouseButton(window, button) == GLFW_RELEASE)
			return true;

		return false;
	}



	bool GLFWInput::MouseButtonDownOnce(unsigned int button)
	{
		return false;
	}



	double GLFWInput::GetMouseX()
	{
		Application& app = Application::Get();
		GLFWwindow* window = static_cast<GLFWwindow*>(app.GetWindow().GetNativeWindow());

		double x, y;

		glfwGetCursorPos(window, &x, &y);

		return x;
	}



	double GLFWInput::GetMouseY()
	{
		Application& app = Application::Get();
		GLFWwindow* window = static_cast<GLFWwindow*>(app.GetWindow().GetNativeWindow());

		double x, y;

		glfwGetCursorPos(window, &x, &y);

		return y;
	}



	double GLFWInput::GetMouseScroll()
	{
		return s_ScrollY;
	}



	MousePos GLFWInput::GetMousePos()
	{
		Application& app = Application::Get();
		GLFWwindow* window = static_cast<GLFWwindow*>(app.GetWindow().GetNativeWindow());

		double x, y;

		glfwGetCursorPos(window, &x, &y);

		return MousePos(x, y);
	}




	void GLFWInput::OnUpdate()
	{

		//Reset scroll variables.
		s_ScrollX = 0;
		s_ScrollY = 0;
	}
}
