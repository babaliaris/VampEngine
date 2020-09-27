#include "pch.h"
#include "OpenGLBuffer.h"
#include "OpenGLError.h"
#include "OpenGLTexture.h"
#include <VampAssert.h>
#include <glad/glad.h>

VampEngine::OpenGLVertexBuffer::OpenGLVertexBuffer(const void* data, unsigned int size, BufferLayout& layout)
	: VertexBuffer(layout), m_id(0)
{

	//Generate The buffer.
	VAMP_GLCALL(glGenBuffers(1, &m_id));

	//Bind the Buffer => Upload the data => Unbind the Buffer.
	VAMP_GLCALL(glBindBuffer(GL_ARRAY_BUFFER, m_id));
	VAMP_GLCALL(glBufferData(GL_ARRAY_BUFFER, size, data, GL_STATIC_DRAW));
	VAMP_GLCALL(glBindBuffer(GL_ARRAY_BUFFER, 0));

}


VampEngine::OpenGLVertexBuffer::~OpenGLVertexBuffer()
{
	VAMP_GLCALL(glDeleteBuffers(1, &m_id));
}



void VampEngine::OpenGLVertexBuffer::Bind() const
{
	VAMP_GLCALL(glBindBuffer(GL_ARRAY_BUFFER, m_id));
}



void VampEngine::OpenGLVertexBuffer::Unbind() const
{
	VAMP_GLCALL(glBindBuffer(GL_ARRAY_BUFFER, 0));
}







VampEngine::OpenGLIndexBuffer::OpenGLIndexBuffer(const void* data, unsigned int size)
	: m_id(0), m_count( size / sizeof(unsigned int))

{
	//Generate The buffer.
	VAMP_GLCALL(glGenBuffers(1, &m_id));

	//Bind the Buffer => Upload the data => Unbind the Buffer.
	VAMP_GLCALL(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_id));
	VAMP_GLCALL(glBufferData(GL_ELEMENT_ARRAY_BUFFER, size, data, GL_STATIC_DRAW));
	VAMP_GLCALL(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0));
}




VampEngine::OpenGLIndexBuffer::~OpenGLIndexBuffer()
{
	VAMP_GLCALL(glDeleteBuffers(1, &m_id));
}




void VampEngine::OpenGLIndexBuffer::Bind() const
{
	VAMP_GLCALL(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_id));
}




void VampEngine::OpenGLIndexBuffer::Unbind() const
{
	VAMP_GLCALL(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0));
}




unsigned int VampEngine::OpenGLIndexBuffer::GetCount() const
{
	return m_count;
}











VampEngine::OpenGLFrameBuffer::OpenGLFrameBuffer(const FrameBufferProps& props)
	: m_id(0), m_renderbuffer(0), m_props(props), m_colorTexture(nullptr), m_depthTexture(nullptr)
{

	//Generate and Bind the framebuffer.
	VAMP_GLCALL(glGenFramebuffers(1, &m_id));
	VAMP_GLCALL(glBindFramebuffer(GL_FRAMEBUFFER, m_id));



	//Create a color attachment.
	if ( ( m_props.mask & VAMP_FRAMEBUFFER_COLOR ) == VAMP_FRAMEBUFFER_COLOR)
	{

		//Create the color attachment texture and bind it.
		m_colorTexture = Texture2D::CreateAttachment(m_props.width, m_props.height, TextureAttachment::COLOR);
		m_colorTexture->Bind();

		//Connect the attachment.
		VAMP_GLCALL(glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, m_colorTexture->GetID(), 0));

		//Unbind the texture.
		m_colorTexture->Unbind();
	}


	//Create a depth attachment.
	if ((m_props.mask & VAMP_FRAMEBUFFER_DEPTH) == VAMP_FRAMEBUFFER_DEPTH)
	{
		//Create the color attachment texture and bind it.
		m_depthTexture = Texture2D::CreateAttachment(m_props.width, m_props.height, TextureAttachment::DEPTH);
		m_depthTexture->Bind();

		//Connect the attachment.
		VAMP_GLCALL(glFramebufferTexture2D(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_TEXTURE_2D, m_depthTexture->GetID(), 0));

		//Unbind the texture.
		m_depthTexture->Unbind();
	}


	//Create a depth-stencil attachment.
	if ((m_props.mask & VAMP_FRAMEBUFFER_DEPTH_STENCIL) == VAMP_FRAMEBUFFER_DEPTH_STENCIL)
	{

		//DEPTH should not be in the mask.
		VAMP_ASSERT((m_props.mask & VAMP_FRAMEBUFFER_DEPTH) != VAMP_FRAMEBUFFER_DEPTH, "You can't specify DEPTH and DEPTH_STENCIL together!");

		//Create and bind the render buffer.
		VAMP_GLCALL(glGenRenderbuffers(1, &m_renderbuffer));
		VAMP_GLCALL(glBindRenderbuffer(GL_RENDERBUFFER, m_renderbuffer));

		//Allocate memory for the renderbuffer.
		VAMP_GLCALL(glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH24_STENCIL8, m_props.width, m_props.height));

		//Connect the render buffer to the framebuffer.
		VAMP_GLCALL(glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_RENDERBUFFER, m_renderbuffer));

		//Unbind the render buffer.
		VAMP_GLCALL(glBindRenderbuffer(GL_RENDERBUFFER, 0));


	}


	//Unbind the framebuffer.
	VAMP_GLCALL(glBindFramebuffer(GL_FRAMEBUFFER, 0));

}



VampEngine::OpenGLFrameBuffer::~OpenGLFrameBuffer()
{

	//Delete this framebuffer.
	VAMP_GLCALL(glDeleteFramebuffers(1, &m_id));

	//Delete the render buffer.
	if (m_renderbuffer > 0)
	{
		VAMP_GLCALL(glDeleteRenderbuffers(1, &m_renderbuffer));
	}

	//Delete the color texture.
	if (m_colorTexture)
		delete m_colorTexture;

	//Delete the depth texture.
	if (m_depthTexture)
		delete m_depthTexture;
}



void VampEngine::OpenGLFrameBuffer::Bind() const
{
	VAMP_GLCALL(glBindFramebuffer(GL_FRAMEBUFFER, m_id));
}



void VampEngine::OpenGLFrameBuffer::Unbind() const
{
	VAMP_GLCALL(glBindFramebuffer(GL_FRAMEBUFFER, 0));
}



void VampEngine::OpenGLFrameBuffer::Update(unsigned int width, unsigned int height)
{

	//Update the props width and height values.
	m_props.width  = width;
	m_props.height = height;


	//Update the color attachment.
	if (m_colorTexture)
	{
		m_colorTexture->UpdateAttachment(width, height);
	}


	//Update the depth texture..
	if (m_depthTexture)
	{
		m_depthTexture->UpdateAttachment(width, height);
	}


	//Update the render buffer..
	if (m_renderbuffer > 0)
	{

		//Bind The Render Buffer.
		VAMP_GLCALL(glBindRenderbuffer(GL_RENDERBUFFER, m_renderbuffer));

		//Re-Allocate memory for the renderbuffer.
		VAMP_GLCALL(glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH24_STENCIL8, width, width));

		//Unbind The Render Buffer.
		VAMP_GLCALL(glBindRenderbuffer(GL_RENDERBUFFER, 0));

	}
}



VampEngine::Texture2D* VampEngine::OpenGLFrameBuffer::GetColorTexture() const
{
	return m_colorTexture;
}



VampEngine::Texture2D* VampEngine::OpenGLFrameBuffer::GetDepthTexture() const
{
	return m_depthTexture;
}
