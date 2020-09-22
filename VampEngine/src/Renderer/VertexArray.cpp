#include "pch.h"
#include "VertexArray.h"

#ifdef VAMP_OPENGL
	#include "Platform/OpenGL/OpenGLVertexArray.h"
#endif

namespace VampEngine
{
	VertexArray* VertexArray::Create()
	{
		#ifdef VAMP_OPENGL
			return new OpenGLVertexArray();
		#endif
	}



	VertexArray::VertexArray()
		: m_IndexBuffer(nullptr)
	{
	}
}