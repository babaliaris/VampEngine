#pragma once
#include <iostream>
#include <sstream>
#include <functional>

#define VAMP_BIND(fn) std::bind(&fn, this, std::placeholders::_1)

namespace VampEngine
{

	enum class EventType
	{
		NONE,
		WINDOW_RESIZE, WINDOW_MOVE, WINDOW_FOCUS, WINDOW_LOST_FOCUS, WINDOW_CLOSE,
		KEY_PRESS, KEY_RELEASE, KEY_REPEAT,
		MOUSE_PRESS, MOUSE_RELEASE, MOUSE_MOVE, MOUSE_SCROLL
	};

	enum class EventCategory
	{
		NONE,
		WINDOW,
		KEYBOARD,
		MOUSE
	};






	class Event
	{

		//Public Members.
		public:
			bool handled = false;


		//Public Methods.
		public:

			//Constructors.
			Event(EventType type, EventCategory category)
				: m_type(type), m_category(category)
			{}

			//Inline Methods.
			inline EventType GetType() const { return m_type; }
			inline EventCategory GetCategory() const { return m_category; }


		//Protected Members.
		protected:
			EventType		m_type;
			EventCategory	m_category;

	};





	class Dispatcher
	{

		//Callback function Type.
		template<typename T>
		using callback = std::function<bool(T&)>;


		//Public Methods.
		public:
			
			//Constructors.
			Dispatcher(Event& event)
				: m_event(event)
			{
			}

			//Dispatch Method.
			template<typename T>
			void Dispatch(callback<T> clb)
			{
				//If the event type is qual to the template event type.
				if (m_event.GetType() == T::GetStaticType())
					clb(  (T&)m_event );
			}

		//Private Members.
		private:
			Event& m_event;
	};
}