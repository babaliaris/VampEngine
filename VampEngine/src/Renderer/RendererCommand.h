#pragma once
#include "VertexArray.h"
#include <glm/glm.hpp>

namespace VampEngine
{

	//Forward Declerations//
	class Window;
	//Forward Declerations//

	class RendererCommand
	{
		friend class Application;

		//Public Static Methods.
		public:

			//Get Method.
			inline static RendererCommand* Get() { return s_Instance; }

		//Public Virtual Methods.
		public:

			//Virtual Deconstructor.
			virtual ~RendererCommand() = default;

			virtual void Init(Window *window) const = 0;

			virtual void SetClearColor(const glm::vec4& color)	const = 0;
			virtual void Clear()								const = 0;

			virtual void SetViewport(int x, int y, unsigned int width, unsigned int height) const = 0;

			virtual void DrawIndexed(VertexArray *vao)			const = 0;

		//Private Methods.
		private:

			//Create Method.
			static void Create();

		//Private Members/
		private:
			static RendererCommand* s_Instance;

	};
}