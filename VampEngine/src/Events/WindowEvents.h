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
		WindowMoveEvent()
			: Event(EventType::WINDOW_MOVE, EventCategory::WINDOW)
		{}

		//To String Method.
		std::string ToString() const
		{
			std::stringstream ss;
			ss << "WindowMoveEvent";
			return ss.str();
		}

		//Static Methods.
		static EventType GetStaticType() { return EventType::WINDOW_MOVE; }
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
}