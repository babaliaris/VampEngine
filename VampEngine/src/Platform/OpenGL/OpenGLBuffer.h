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



	class OpenGLFrameBuffer : public FrameBuffer
	{

		//Public Methods.
		public:
			OpenGLFrameBuffer(const FrameBufferProps& props);

		//Public Virtual Methods.
		public:

			//Default Virtual Deconstructor.
			virtual ~OpenGLFrameBuffer();

			//Bind and Unbind.
			virtual void Bind()		const override;
			virtual void Unbind()	const override;

			//Update Method.
			virtual void Update(unsigned int width, unsigned int height) override;

			//Get Methods.
			virtual Texture2D* GetColorTexture() const override;
			virtual Texture2D* GetDepthTexture() const override;

		//Private Members.
		private:
			unsigned int		m_id, m_renderbuffer;
			FrameBufferProps	m_props;

			Texture2D* m_colorTexture;
			Texture2D* m_depthTexture;

	};
}