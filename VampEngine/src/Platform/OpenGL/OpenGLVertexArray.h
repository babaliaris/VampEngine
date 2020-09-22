#pragma once
#include "Renderer/VertexArray.h"

namespace VampEngine
{
	class OpenGLVertexArray : public VertexArray
	{

		//Public Methods.
		public:
			OpenGLVertexArray();

		//Public Virtual Methods.
		public:

			//Virtual Destructor.
			virtual ~OpenGLVertexArray();

			//Bind and Unbind Methods.
			virtual void Bind()		const override;
			virtual void Unbind()	const override;

			//Add Buffer and Set Index Buffer Methods.
			virtual void AddBuffer(VertexBuffer * vbo)		override;
			virtual void SetIndexBuffer(IndexBuffer * ebo)	override;

		//Private Members.
		private:
			unsigned int m_id;

	};
}