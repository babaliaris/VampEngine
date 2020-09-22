#pragma once
#include "Input/Input.h"

namespace VampEngine
{
	class GLFWInput : public Input
	{

		public:

			GLFWInput();
			virtual ~GLFWInput();

			virtual bool KeyDown(unsigned int keycode) override;
			virtual bool KeyUp(unsigned int keycode) override;
			virtual bool KeyDownOnce(unsigned int keycode) override;

			virtual bool MouseButtonDown(unsigned int button) override;
			virtual bool MouseButtonUp(unsigned int button) override;
			virtual bool MouseButtonDownOnce(unsigned int button) override;

			virtual double GetMouseX() override;
			virtual double GetMouseY() override;
			virtual double GetMouseScroll() override;

			virtual MousePos GetMousePos() override;

			virtual void OnUpdate() override;

		private:
			static double s_ScrollX, s_ScrollY;

	};
}