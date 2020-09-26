#include "TextureLayer.h"

TextureLayer::TextureLayer()
{
}

TextureLayer::~TextureLayer()
{
}

void TextureLayer::OnAttach()
{
	float vertices[] =
	{

		 //Positions.			//Texture Coordinates.
		-0.5f,  0.5f, 0.0f,		0.0f, 1.0f,		// Top LEFT     => 0
		 0.5f,  0.5f, 0.0f,		1.0f, 1.0f,		// Top RIGHT    => 1
		-0.5f, -0.5f, 0.0f,		0.0f, 0.0f,		// Bottom LEFT  => 2
		 0.5f, -0.5f, 0.0f,		1.0f, 0.0f		// Bottom RIGHT => 3
	};

	unsigned int indices[] =
	{
		0, 2, 3,
		1, 0, 3
	};

	m_vao = VampEngine::VertexArray::Create();

	VampEngine::BufferLayout layout =
	{
		{VampEngine::BufferDataType::FLOAT3, "positions"},
		{VampEngine::BufferDataType::FLOAT2, "text coords"}
	};

	VampEngine::VertexBuffer* vbo = VampEngine::VertexBuffer::Create(vertices, sizeof(vertices), layout);
	VampEngine::IndexBuffer* ebo  = VampEngine::IndexBuffer::Create(indices, sizeof(indices));

	m_vao->AddBuffer(vbo);
	m_vao->SetIndexBuffer(ebo);

	VampEngine::ShaderProps shaderProps("src/Shaders/TexturedQuad.vert", "src/Shaders/TexturedQuad.frag");
	m_shader = VampEngine::Shader::Create(shaderProps);

	VampEngine::Texture2DProps  textureProps("Assets/Checkerboard.jpg");
	m_texture = VampEngine::Texture2D::CreateTexture2D(textureProps);
}

void TextureLayer::OnDetatch()
{
}

void TextureLayer::OnUpdate()
{
	m_vao->Bind();
	m_shader->Bind();
	m_texture->Bind();
	VampEngine::RendererCommand::Get()->DrawIndexed(m_vao);
}

void TextureLayer::OnEvent(VampEngine::Event& e)
{
}
