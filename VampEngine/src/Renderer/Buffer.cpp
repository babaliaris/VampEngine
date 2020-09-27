#include "pch.h"
#include "Buffer.h"
#include <VampAssert.h>

#ifdef VAMP_OPENGL
	#include "Platform/OpenGL/OpenGLBuffer.h"
#endif

namespace VampEngine
{

	//=========================Vertex Buffer Class Implementation=========================//
	VertexBuffer* VertexBuffer::Create(const void* data, unsigned int size, BufferLayout& layout)
	{
		#ifdef VAMP_OPENGL
			return new OpenGLVertexBuffer(data, size, layout);
		#endif
	}

	VertexBuffer::VertexBuffer(BufferLayout& layout)
		: m_layout(layout)
	{
	}

	void VertexBuffer::SetLayout(const BufferLayout& layout)
	{
		m_layout = layout;
	}
	//=========================Vertex Buffer Class Implementation=========================//




	//=========================Index Buffer Class Implementation=========================//
	IndexBuffer* IndexBuffer::Create(const void* data, unsigned int size)
	{
		#ifdef VAMP_OPENGL
			return new OpenGLIndexBuffer(data, size);
		#endif
	}
	//=========================Index Buffer Class Implementation=========================//




	//=========================Frame Buffer Class Implementation=========================//
	FrameBuffer* FrameBuffer::Create(const FrameBufferProps& props)
	{
		#ifdef VAMP_OPENGL
			return new OpenGLFrameBuffer(props);
		#endif
	}


	FrameBufferProps::FrameBufferProps()
		: mask(VAMP_FRAMEBUFFER_COLOR | VAMP_FRAMEBUFFER_DEPTH_STENCIL), width(0), height(0), colorSamples(0)
	{
	}


	FrameBufferProps::FrameBufferProps(unsigned int mask, unsigned int width, unsigned int height)
		: mask(mask), width(width), height(height), colorSamples(0)
	{
	}
	//=========================Frame Buffer Class Implementation=========================//



	unsigned int GetBufferDataTypeCount(BufferDataType type)
	{
		switch (type)
		{
		case VampEngine::BufferDataType::FLOAT: return 1;
		case VampEngine::BufferDataType::FLOAT2: return 2;
		case VampEngine::BufferDataType::FLOAT3: return 3;
		case VampEngine::BufferDataType::FLOAT4: return 4;
		case VampEngine::BufferDataType::INT: return 1;
		case VampEngine::BufferDataType::INT2: return 2;
		case VampEngine::BufferDataType::INT3: return 3;
		case VampEngine::BufferDataType::INT4: return 4;
		case VampEngine::BufferDataType::BOOL: return 1;
		case VampEngine::BufferDataType::BOOL2: return 2;
		case VampEngine::BufferDataType::BOOL3: return 3;
		case VampEngine::BufferDataType::BOOL4: return 4;
		case VampEngine::BufferDataType::MAT3: return 3 * 3;
		case VampEngine::BufferDataType::MAT4: return 4 * 4;
		}

		VAMP_ASSERT(0, "Uknown DataType");

		return 0;
	}




	unsigned int GetBufferDataTypeSize(BufferDataType type)
	{
		switch (type)
		{
		case VampEngine::BufferDataType::FLOAT: return 4;
		case VampEngine::BufferDataType::FLOAT2: return 2 * 4;
		case VampEngine::BufferDataType::FLOAT3: return 3 * 4;
		case VampEngine::BufferDataType::FLOAT4: return 4 * 4;
		case VampEngine::BufferDataType::INT: return 4;
		case VampEngine::BufferDataType::INT2: return 2 * 4;
		case VampEngine::BufferDataType::INT3: return 3 * 4;
		case VampEngine::BufferDataType::INT4: return 4 * 4;
		case VampEngine::BufferDataType::BOOL: return 1;
		case VampEngine::BufferDataType::BOOL2: return 2;
		case VampEngine::BufferDataType::BOOL3: return 3;
		case VampEngine::BufferDataType::BOOL4: return 4;
		case VampEngine::BufferDataType::MAT3: return 3 * 3 * 4;
		case VampEngine::BufferDataType::MAT4: return 4 * 4 * 4;
		}

		VAMP_ASSERT(0, "Uknown DataType");

		return 0;
	}




	//Layout Attribute Constructor.
	LayoutAttribute::LayoutAttribute(BufferDataType type, const std::string& name)
		:	type(type), name(name), count(GetBufferDataTypeCount(type)),
			size(GetBufferDataTypeSize(type)), offset(0)
	{}



	//=========================Layout Class Implementation=========================//
	BufferLayout::BufferLayout(const std::initializer_list<LayoutAttribute>& attributes)
	{
		//Set the attributes.
		m_attributes = attributes;

		//Calculate the attributes.
		this->CalculateAttributes();
	}


	std::vector<LayoutAttribute>::iterator BufferLayout::begin()
	{
		return m_attributes.begin();
	}


	std::vector<LayoutAttribute>::iterator BufferLayout::end()
	{
		return m_attributes.end();
	}


	std::vector<LayoutAttribute>::const_iterator BufferLayout::begin() const
	{
		return m_attributes.begin();
	}


	std::vector<LayoutAttribute>::const_iterator BufferLayout::end() const
	{
		return m_attributes.end();
	}



	void BufferLayout::CalculateAttributes()
	{
		//Reset the stride.
		m_stride = 0;

		//Calculate.
		unsigned int offset = 0;
		for (LayoutAttribute& attribute : m_attributes)
		{

			//Set the attribute offset.
			attribute.offset = offset;

			//Increase stride and offset.
			m_stride	+= attribute.size;
			offset		+= attribute.size;
		}
	}
	//=========================Layout Class Implementation=========================//
}