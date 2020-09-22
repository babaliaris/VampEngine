#include "pch.h"
#include "OpenGLBuffer.h"
#include "OpenGLError.h"
#include <glad/glad.h>

VampEngine::OpenGLVertexBuffer::OpenGLVertexBuffer(const void* data, unsigned int size, BufferLayout& layout)
	: VertexBuffer(layout), m_id(0)
{

	//Generate The buffer.
	VAMP_GLCALL(glGenBuffers(1, &m_id));

	//Bind the Buffer => Uploda the data => Unbind the Buffer.
	VAMP_GLCALL(glBindBuffer(GL_UNSIGNED_BYTE, m_id));
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

	//Bind the Buffer => Uploda the data => Unbind the Buffer.
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
	VAMP_GLCALL(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0));//
}




unsigned int VampEngine::OpenGLIndexBuffer::GetCount() const
{
	return m_count;
}
