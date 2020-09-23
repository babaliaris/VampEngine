#include "pch.h"
#include "GFLWWindow.h"
#include "Core/Core.h"
#include "Events/KeyEvents.h"
#include "Events/MouseEvents.h"
#include "Events/WindowEvents.h"
#include <GLFW/glfw3.h>
#include "Renderer/RendererCommand.h"

namespace VampEngine
{
	GLFWWindow::GLFWWindow(int width, int height, const std::string& title)
		: m_data(width, height, title), m_glfwWindow(NULL)
	{
		this->Init();
	}




	GLFWWindow::~GLFWWindow()
	{
		glfwDestroyWindow(m_glfwWindow);
		glfwTerminate();
	}




	void GLFWWindow::Update() const
	{
		glfwPollEvents();
		glfwSwapBuffers(m_glfwWindow);
	}




	void* GLFWWindow::GetProcAddress() const
	{
		return glfwGetProcAddress;
	}





	void GLFWWindow::Init()
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

		//Create the OpenGL Context.
		glfwMakeContextCurrent(m_glfwWindow);

		//Init the Renderer.
		RendererCommand::Get()->Init(this);

		//Set The Viewport.
		RendererCommand::Get()->SetViewport(0, 0, m_data.width, m_data.height);

		//Set User Pointer.
		glfwSetWindowUserPointer(m_glfwWindow, (void*)&m_data);

		//Connect the event system.
		this->ConnectEventSystem();
	}





	void GLFWWindow::ConnectEventSystem()
	{

		//Window Resize Event.
		glfwSetWindowSizeCallback(m_glfwWindow, [](GLFWwindow *window, int width, int height)
		{

				//Get The GLFW User Pointer.
				WindowData& data = *(WindowData *)glfwGetWindowUserPointer(window);

				//Create The Event.
				WindowResizeEvent e(width, height);

				//Update Window Data.
				data.width  = e.GetWidth();
				data.height = e.GetHeight();

				//Update The Viewport.
				RendererCommand::Get()->SetViewport(0, 0, data.width, data.height);

				//Check if the window is minimized.
				if (data.width == 0 || data.height == 0)
					data.minimized = true;

				//Else it's not minimized.
				else
					data.minimized = false;

				//Send the event.
				data.callback(e);
		});



		//Window Move Event.
		glfwSetWindowPosCallback(m_glfwWindow, [](GLFWwindow* window, int x, int y)
		{
				//Get The GLFW User Pointer.
				WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);

				//Create The Event.
				WindowMoveEvent e(x, y);

				//Update Window Data.
				data.x = e.GetX();
				data.y = e.GetY();

				//Send the event.
				data.callback(e);
		});



		//WindowFocesEvent and WindowLostFocusEvent.
		glfwSetWindowFocusCallback(m_glfwWindow, [](GLFWwindow* window, int focus)
		{
				//Get The GLFW User Pointer.
				WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);

				//Focus.
				if (focus == GLFW_TRUE)
				{
					WindowFocusEvent e;
					data.callback(e);
				}

				//Lost Focus.
				else
				{
					WindowLostFocusEvent e;
					data.callback(e);
				}
		});



		//Window Close Event.
		glfwSetWindowCloseCallback(m_glfwWindow, [](GLFWwindow* window)
		{
				//Get The GLFW User Pointer.
				WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);

				//Create The Event.
				WindowCloseEvent e;

				//Send The Event.
				data.callback(e);
		});



		//Key Events.
		glfwSetKeyCallback(m_glfwWindow, [](GLFWwindow* window, int code, int scancode, int action, int mods)
		{
				//Get The GLFW User Pointer.
				WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);

				//Switch The Key Action.
				switch (action)
				{

					//Key Pressed.
					case GLFW_PRESS:
					{
						KeyPressEvent e(code);
						data.callback(e);
						break;
					}

					//key Released.
					case GLFW_RELEASE:
					{
						KeyReleaseEvent e(code);
						data.callback(e);
						break;
					}

					//Key Repeated.
					case GLFW_REPEAT:
					{
						KeyRepeatEvent e(code, 1);
						data.callback(e);
						break;
					}

					//Don't do anything.
					default:
						break;
				}
		});



		//Mouse Press Events.
		glfwSetMouseButtonCallback(m_glfwWindow, [](GLFWwindow* window, int button, int action, int mods)
		{
				//Get The GLFW User Pointer.
				WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);

				//Switch The Key Action.
				switch (action)
				{

				//Key Pressed.
				case GLFW_PRESS:
				{
					MousePressEvent e(button);
					data.callback(e);
					break;
				}

				//key Released.
				case GLFW_RELEASE:
				{
					MouseReleaseEvent e(button);
					data.callback(e);
					break;
				}

				//Don't do anything.
				default:
					break;
				}
		});



		//Cursor Position Event.
		glfwSetCursorPosCallback(m_glfwWindow, [](GLFWwindow* window, double x, double y)
		{
				//Get The GLFW User Pointer.
				WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);

				//Create the Event.
				MouseMoveEvent e(x, y);

				//Send the event.
				data.callback(e);
		});



		//Scroll Event.
		glfwSetScrollCallback(m_glfwWindow, [](GLFWwindow* window, double x, double y)
		{
				//Get The GLFW User Pointer.
				WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);

				//Create the Event.
				MouseScrollEvent e(x, y);

				//Send the event.
				data.callback(e);
		});


		
	}
}