#pragma once
#include "Event.h"

namespace VampEngine
{
	class WindowResizeEvent : public Event
	{

		//Public Methods.
		public:

			//Contructors.
			WindowResizeEvent(unsigned int width, unsigned int height)
				: Event(EventType::WINDOW_RESIZE, EventCategory::WINDOW), m_width(width), m_height(height)
			{}

			//To String Method.
			std::string ToString() const
			{
				std::stringstream ss;
				ss << "WindowResizeEvent => Width: " << m_width << " , Height: " << m_height;
				return ss.str();
			}

			//Inline Methods.
			inline unsigned int GetWidth() const { return m_width; }
			inline unsigned int GetHeight() const { return m_height; }

			//Static Methods.
			static EventType GetStaticType() { return EventType::WINDOW_RESIZE; }


		//Private Members.
		private:
			unsigned int m_width, m_height;

	};




	class WindowMoveEvent : public Event
	{

		//Public Methods.
		public:

		//Contructors.
		WindowMoveEvent(int x, int y)
			: Event(EventType::WINDOW_MOVE, EventCategory::WINDOW), m_x(x), m_y(y)
		{}

		//To String Method.
		std::string ToString() const
		{
			std::stringstream ss;
			ss << "WindowMoveEvent => X: " << m_x << " , Y: " << m_y;
			return ss.str();
		}

		//Inline Methods.
		inline unsigned int GetX() const { return m_x; }
		inline unsigned int GetY() const { return m_y; }

		//Static Methods.
		static EventType GetStaticType() { return EventType::WINDOW_MOVE; }

		//Private Members.
		private:
			int m_x, m_y;
	};




	class WindowFocusEvent : public Event
	{

		//Public Methods.
		public:

		//Contructors.
		WindowFocusEvent()
			: Event(EventType::WINDOW_FOCUS, EventCategory::WINDOW)
		{}

		//To String Method.
		std::string ToString() const
		{
			std::stringstream ss;
			ss << "WindowFocusEvent";
			return ss.str();
		}

		//Static Methods.
		static EventType GetStaticType() { return EventType::WINDOW_FOCUS; }
	};




	class WindowLostFocusEvent : public Event
	{

		//Public Methods.
		public:

		//Contructors.
		WindowLostFocusEvent()
			: Event(EventType::WINDOW_LOST_FOCUS, EventCategory::WINDOW)
		{}

		//To String Method.
		std::string ToString() const
		{
			std::stringstream ss;
			ss << "WindowLostFocusEvent";
			return ss.str();
		}

		//Static Methods.
		static EventType GetStaticType() { return EventType::WINDOW_LOST_FOCUS; }
	};




	class WindowCloseEvent : public Event
	{

		//Public Methods.
		public:

		//Contructors.
		WindowCloseEvent()
			: Event(EventType::WINDOW_CLOSE, EventCategory::WINDOW)
		{}

		//To String Method.
		std::string ToString() const
		{
			std::stringstream ss;
			ss << "WindowCloseEvent";
			return ss.str();
		}

		//Static Methods.
		static EventType GetStaticType() { return EventType::WINDOW_CLOSE; }
	};
}