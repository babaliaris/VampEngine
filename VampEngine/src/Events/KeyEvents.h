#pragma once
#include "Event.h"

namespace VampEngine
{
	class KeyEvent : public Event
	{

		//Public Methods.
		public:

		//Contructors.
		KeyEvent(EventType type, EventCategory category, unsigned int keycode)
			: Event(type, category), m_keycode(keycode)
		{}

		//Inline Methods.
		inline unsigned int GetKeycode() const { return m_keycode; }

		//Private Members.
		protected:
		unsigned int m_keycode;

	};




	class KeyPressEvent : public KeyEvent
	{

		//Public Methods.
		public:

		//Contructors.
		KeyPressEvent(unsigned int keycode)
			: KeyEvent(EventType::KEY_PRESS, EventCategory::KEYBOARD, keycode)
		{}

		//To String Method.
		std::string ToString() const
		{
			std::stringstream ss;
			ss << "KeyPressEvent => Keycode: " << m_keycode;
			return ss.str();
		}

		//Static Methods.
		static EventType GetStaticType() { return EventType::KEY_PRESS; }
	};




	class KeyReleaseEvent : public KeyEvent
	{

		//Public Methods.
		public:

		//Contructors.
		KeyReleaseEvent(unsigned int keycode)
			: KeyEvent(EventType::KEY_RELEASE, EventCategory::KEYBOARD, keycode)
		{}

		//To String Method.
		std::string ToString() const
		{
			std::stringstream ss;
			ss << "KeyReleaseEvent => Keycode: " << m_keycode;
			return ss.str();
		}

		//Static Methods.
		static EventType GetStaticType() { return EventType::KEY_RELEASE; }
	};





	class KeyRepeatEvent : public KeyEvent
	{

		//Public Methods.
		public:

		//Contructors.
		KeyRepeatEvent(unsigned int keycode, unsigned int repeats)
			: KeyEvent(EventType::KEY_REPEAT, EventCategory::KEYBOARD, keycode), m_repeats(repeats)
		{}

		//To String Method.
		std::string ToString() const
		{
			std::stringstream ss;
			ss << "KeyRepeatEvent => Keycode: " << m_keycode << " , Repeats: " << m_repeats;
			return ss.str();
		}

		//Inline Methods.
		inline unsigned int GetRepeats() const { return m_repeats; }

		//Static Methods.
		static EventType GetStaticType() { return EventType::KEY_REPEAT; }

		private:
			unsigned int m_repeats;
	};


}