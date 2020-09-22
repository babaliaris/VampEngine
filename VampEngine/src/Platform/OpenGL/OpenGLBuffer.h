#pragma once
#include "Renderer/Buffer.h"

namespace VampEngine
{
	class OpenGLVertexBuffer : public VertexBuffer
	{

		//Public Methods.
		public:
			OpenGLVertexBuffer(const void* data, unsigned int size, BufferLayout& layout);

		//Public Virtual Methods.
		public:
			virtual ~OpenGLVertexBuffer();
			virtual void Bind() const override;
			virtual void Unbind() const override;

		//Private Members.
		private:
			unsigned int m_id = 0;
	};





	class OpenGLIndexBuffer : public IndexBuffer
	{

		//Public Methods.
		public:
			OpenGLIndexBuffer(const void* data, unsigned int size);

		//Public Virtual Methods.
		public:
			virtual ~OpenGLIndexBuffer();
			virtual void Bind() const override;
			virtual void Unbind() const override;
			virtual unsigned int GetCount() const override;


		//Private Members.
		private:
			unsigned int m_id, m_count;
	};
}