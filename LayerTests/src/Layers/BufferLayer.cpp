#include "BufferLayer.h"

BufferLayer::BufferLayer()
{
}

BufferLayer::~BufferLayer()
{
}

void BufferLayer::OnAttach()
{
	float vertices[] =
	{
		0.0f,  0.5f, 0.0f,	//0 Upper.
	   -0.5f, -0.5f, 0.0f,	//1 left.
		0.5f, -0.5f, 0.0f	//2 right.
	};

	float indices[] =
	{
		0, 1, 2
	};

	VampEngine::BufferLayout layout =
	{
		{VampEngine::BufferDataType::FLOAT3, "positions"}
	};

	VampEngine::VertexBuffer* vbo	= VampEngine::VertexBuffer::Create(vertices, sizeof(vertices), layout);
	VampEngine::IndexBuffer* ebo	= VampEngine::IndexBuffer::Create(indices, sizeof(indices));

}

void BufferLayer::OnDetatch()
{
}

void BufferLayer::OnUpdate()
{
}

void BufferLayer::OnEvent(VampEngine::Event& e)
{
}