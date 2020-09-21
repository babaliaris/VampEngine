#pragma once

namespace VampEngine
{

	//Forward Declerations//
	class Event;
	//Forward Declerations//

	class Layer
	{

		//Public Members.
		public:
			bool active = true;

		//Public Methods.
		public:

		//Constructors.
		virtual ~Layer() = default;


		//Other Virtual Methods.
		virtual void OnAttach();
		virtual void OnDetatch();
		virtual void OnUpdate();
		virtual void OnEvent(Event& e);
	};
}

