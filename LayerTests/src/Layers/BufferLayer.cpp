#include "BufferLayer.h"
#include <glad/glad.h>

BufferLayer::BufferLayer()
	: m_vao(nullptr)
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

	unsigned int indices[] =
	{
		0, 1, 2
	};

	
	m_vao = VampEngine::VertexArray::Create();

	VampEngine::BufferLayout layout =
	{
		{VampEngine::BufferDataType::FLOAT3, "positions"}
	};

	
	VampEngine::VertexBuffer* vbo	= VampEngine::VertexBuffer::Create(vertices, sizeof(vertices), layout);
	VampEngine::IndexBuffer* ebo	= VampEngine::IndexBuffer::Create(indices, sizeof(indices));

	vbo->Bind();
	ebo->Bind();

	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 12, 0);

	m_vao->AddBuffer(vbo);
	m_vao->SetIndexBuffer(ebo);

	VampEngine::ShaderProps props("src/Shaders/Basic.vert", "src/Shaders/Basic.frag", "src/Shaders/Basic.geom");
	m_shader = VampEngine::Shader::Create(props);
	
}

void BufferLayer::OnDetatch()
{
}

void BufferLayer::OnUpdate()
{
	m_shader->Bind();
	VampEngine::RendererCommand::Get()->DrawIndexed(m_vao);
}

void BufferLayer::OnEvent(VampEngine::Event& e)
{
}