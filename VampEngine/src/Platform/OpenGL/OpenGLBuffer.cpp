#include "pch.h"
#include "OpenGLBuffer.h"
#include <glad/glad.h>

VampEngine::OpenGLVertexBuffer::OpenGLVertexBuffer(const void* data, unsigned int size, BufferLayout& layout)
	: VertexBuffer(layout), m_id(0)
{

	//Generate The buffer.
	glGenBuffers(1, &m_id);

	//Bind the Buffer => Uploda the data => Unbind the Buffer.
	glBindBuffer(GL_ARRAY_BUFFER, m_id);
	glBufferData(GL_ARRAY_BUFFER, size, data, GL_STATIC_DRAW);
	glBindBuffer(GL_ARRAY_BUFFER, 0);

}


VampEngine::OpenGLVertexBuffer::~OpenGLVertexBuffer()
{
	glDeleteBuffers(1, &m_id);
}



void VampEngine::OpenGLVertexBuffer::Bind() const
{
	glBindBuffer(GL_ARRAY_BUFFER, m_id);
}



void VampEngine::OpenGLVertexBuffer::Unbind() const
{
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}







VampEngine::OpenGLIndexBuffer::OpenGLIndexBuffer(const void* data, unsigned int size)
	: m_id(0), m_count( size / sizeof(unsigned int))

{
	//Generate The buffer.
	glGenBuffers(1, &m_id);

	//Bind the Buffer => Uploda the data => Unbind the Buffer.
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_id);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, size, data, GL_STATIC_DRAW);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}




VampEngine::OpenGLIndexBuffer::~OpenGLIndexBuffer()
{
	glDeleteBuffers(1, &m_id);
}




void VampEngine::OpenGLIndexBuffer::Bind() const
{
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_id);
}




void VampEngine::OpenGLIndexBuffer::Unbind() const
{
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}




unsigned int VampEngine::OpenGLIndexBuffer::GetCount() const
{
	return m_count;
}
