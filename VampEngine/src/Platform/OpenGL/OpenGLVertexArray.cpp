#include "pch.h"
#include "OpenGLVertexArray.h"
#include "OpenGLError.h"
#include "VampAssert.h"
#include <glad/glad.h>



namespace VampEngine
{
	GLenum VertexBufferDataToOpenGL(BufferDataType type)
	{
		switch (type)
		{
			case VampEngine::BufferDataType::FLOAT	: return GL_FLOAT;
			case VampEngine::BufferDataType::FLOAT2	: return GL_FLOAT;
			case VampEngine::BufferDataType::FLOAT3	: return GL_FLOAT;
			case VampEngine::BufferDataType::FLOAT4	: return GL_FLOAT;
			case VampEngine::BufferDataType::INT	: return GL_INT;
			case VampEngine::BufferDataType::INT2	: return GL_INT;
			case VampEngine::BufferDataType::INT3	: return GL_INT;
			case VampEngine::BufferDataType::INT4	: return GL_INT;
			case VampEngine::BufferDataType::BOOL	: return GL_BOOL;
			case VampEngine::BufferDataType::BOOL2	: return GL_BOOL;
			case VampEngine::BufferDataType::BOOL3	: return GL_BOOL;
			case VampEngine::BufferDataType::BOOL4	: return GL_BOOL;
			case VampEngine::BufferDataType::MAT3	: return GL_FLOAT;
			case VampEngine::BufferDataType::MAT4	: return GL_FLOAT;
		}

		VAMP_ASSERT(0, "Uknown BufferDataType");
		return 0;
	}
}



VampEngine::OpenGLVertexArray::OpenGLVertexArray()
	: m_id(0)
{
	VAMP_GLCALL(glGenVertexArrays(1, &m_id));
}




VampEngine::OpenGLVertexArray::~OpenGLVertexArray()
{
	VAMP_GLCALL(glDeleteVertexArrays(1, &m_id));
}




void VampEngine::OpenGLVertexArray::Bind() const
{
	VAMP_GLCALL(glBindVertexArray(m_id));
}




void VampEngine::OpenGLVertexArray::Unbind() const
{
	VAMP_GLCALL(glBindVertexArray(0));
}




void VampEngine::OpenGLVertexArray::AddBuffer(VertexBuffer* vbo)
{

	//Bind this vertex array.
	this->Bind();

	//Bind the vertex buffer.
	vbo->Bind();

	//For each attribute in the layout.
	unsigned int i = 0;
	for (const LayoutAttribute& attr : vbo->GetLayout())
	{
		//Get the GLtype and the offset.
		GLenum type			= VertexBufferDataToOpenGL(attr.type);
		const void* offset	= (const void*)attr.offset;

		//Enable the Vertex Attribute.
		VAMP_GLCALL(glEnableVertexAttribArray(i));

		//Create The Vertex Attribute.
		VAMP_GLCALL(glVertexAttribPointer(i, attr.count, type, GL_FALSE, vbo->GetLayout().GetStride(), offset));

		//Increase the index.
		i++;
	}

	//Push the VBO into the array of buffers.
	m_vertexBuffers.push_back(vbo);

	//Unbind this vertex arrray.
	this->Unbind();

	//Unbind the vertex buffer.
	vbo->Unbind();
}




void VampEngine::OpenGLVertexArray::SetIndexBuffer(IndexBuffer* ebo)
{
	//Bind this vertex array.
	this->Bind();

	//Bind The Index Buffer.
	ebo->Bind();

	//Set The Index Buffer.
	m_IndexBuffer = ebo;

	//Unbind this vertex arrray.
	this->Unbind();

	//Unbind the index buffer.
	ebo->Unbind();
	
}
