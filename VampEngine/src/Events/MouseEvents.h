#pragma once
#include "Event.h"

namespace VampEngine
{
	class MouseButtonEvent : public Event
	{

		//Public Methods.
		public:

		//Contructors.
		MouseButtonEvent(EventType type, EventCategory category, unsigned int button)
			: Event(type, category), m_button(button)
		{}

		//Inline Methods.
		inline unsigned int GetButton() const { return m_button; }

		//Private Members.
		protected:
		unsigned int m_button;

	};




	class MousePressEvent : public MouseButtonEvent
	{

		//Public Methods.
		public:

		//Contructors.
		MousePressEvent(unsigned int button)
			: MouseButtonEvent(EventType::MOUSE_PRESS, EventCategory::MOUSE, button)
		{}

		//To String Method.
		std::string ToString() const
		{
			std::stringstream ss;
			ss << "MousePressEvent => Button: " << m_button;
			return ss.str();
		}

		//Static Methods.
		static EventType GetStaticType() { return EventType::MOUSE_PRESS; }
	};




	class MouseReleaseEvent : public MouseButtonEvent
	{

		//Public Methods.
		public:

		//Contructors.
		MouseReleaseEvent(unsigned int button)
			: MouseButtonEvent(EventType::MOUSE_RELEASE, EventCategory::MOUSE, button)
		{}

		//To String Method.
		std::string ToString() const
		{
			std::stringstream ss;
			ss << "MouseReleaseEvent => Button: " << m_button;
			return ss.str();
		}

		//Static Methods.
		static EventType GetStaticType() { return EventType::MOUSE_RELEASE; }
	};




	class MouseMoveEvent : public Event
	{

		//Public Methods.
		public:

		//Contructors.
		MouseMoveEvent(double x, double y)
			: Event(EventType::MOUSE_MOVE, EventCategory::MOUSE), m_x(x), m_y(y)
		{}

		//To String Method.
		std::string ToString() const
		{
			std::stringstream ss;
			ss << "MouseMoveEvent => X: " << m_x << " , Y: " << m_y;
			return ss.str();
		}

		//Static Methods.
		static EventType GetStaticType() { return EventType::MOUSE_MOVE; }

		//Private Members.
		private:
			double m_x, m_y;
	};
}