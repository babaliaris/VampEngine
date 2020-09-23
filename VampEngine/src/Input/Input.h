#pragma once

namespace VampEngine
{

	struct MousePos
	{
		double x;
		double y;

		MousePos(double x, double y)
			: x(x), y(y)
		{}
	};



	class Input
	{
		friend class Application;


		//Public Static Methods.
		public:
			static void Create();
			inline static Input* Get() { return s_Instance; };



		//Public Virtual Methods.
		public:

			virtual ~Input() = default;

			virtual bool KeyDown(unsigned int keycode)		= 0;
			virtual bool KeyUp(unsigned int keycode)		= 0;
			virtual bool KeyDownOnce(unsigned int keycode)	= 0;

			virtual bool MouseButtonDown(unsigned int button)		= 0;
			virtual bool MouseButtonUp(unsigned int button)			= 0;
			virtual bool MouseButtonDownOnce(unsigned int button)	= 0;

			virtual double GetMouseX()		= 0;
			virtual double GetMouseY()		= 0;
			virtual double GetMouseScroll() = 0;

			virtual MousePos GetMousePos() = 0;


		//Private Methods.
		private:
			virtual void OnUpdate() = 0;


		//Private Members.
		private:
			static Input *s_Instance;

	};
}