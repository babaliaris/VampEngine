#include "Window.h"
#include <VampAssert.h>
#include <GLFW/glfw3.h>

namespace VampEngine
{
	Window::Window(int width, int height, const std::string& title)
		: m_data(width, height, title), m_glfwWindow(NULL)
	{
		this->Init();
	}




	Window::~Window()
	{
		glfwDestroyWindow(m_glfwWindow);
		glfwTerminate();
	}




	void Window::Update()
	{
		glfwPollEvents();
		glfwSwapBuffers(m_glfwWindow);
	}




	void Window::Init()
	{
		//Initialize GLFW.
		int glfwSuccess = glfwInit();
		VAMP_ASSERT(glfwSuccess, "GLFW failed to be initialized!");

		//OpenGL 3.3 CORE PROFILE.
		glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
		glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
		glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

		//Create the window.
		m_glfwWindow = glfwCreateWindow(m_data.width, m_data.height, m_data.title.c_str(), NULL, NULL);
		VAMP_ASSERT(m_glfwWindow, "GLFW Window could not be created!");

		//Set User Pointer.
		glfwSetWindowUserPointer(m_glfwWindow, (void*)&m_data);
	}
}