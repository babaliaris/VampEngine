#pragma once
#include "Renderer/RendererCommand.h"

namespace VampEngine
{
	class OpenGLRendererCommand : public RendererCommand
	{

		//Public Methods.
		public:
			OpenGLRendererCommand();

		//Public Virtual Methods.
		public:

			//Virtual Deconstructor.
			virtual ~OpenGLRendererCommand();

			virtual void Init(Window *window) const override;

			virtual void SetClearColor(const glm::vec4& color)	const override;
			virtual void Clear()								const override;

			virtual void SetViewport(int x, int y, unsigned int width, unsigned int height) const override;

			virtual void DrawIndexed(VertexArray * vao)			const override;

		//Private Members.
		private:
	};

}