#pragma once
#include <string>
#include <functional>
#include "Events/Event.h"

namespace VampEngine
{

	class Window
	{
		//Event Callback Method Signature.
		using EventCallback = std::function<void(Event&)>;

		//Static Methods.
		public:
			static Window* Create(int width = 800, int height = 600, const std::string& title = "VampEngine");


		//Virtual Methods.
		public:

			//Destructor.
			virtual ~Window() = default;

			//Methods.
			virtual void Update() const = 0;

			//Get Width And Height.
			virtual unsigned int GetWidth() const = 0;
			virtual unsigned int GetHeight() const = 0;

			//Get X, Y, Window Coordinates.
			virtual int GetX() const = 0;
			virtual int GetY() const = 0;

			//Get Window Title.
			virtual const std::string & GetTitle() const = 0;

			//Get Event Callback.
			virtual EventCallback& GetEventCallback() = 0;

			//Check if minimized or maximized.
			virtual bool IsMinimized() const = 0;
			virtual bool IsMaximized() const = 0;

			//Get Native Window.
			virtual void* GetNativeWindow() = 0;

			//Get Proc Address.
			virtual void* GetProcAddress() const = 0;

	};
}