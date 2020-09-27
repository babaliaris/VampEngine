#include "FramebufferLayer.h"

FramebufferLayer::FramebufferLayer()
	: m_window(VampEngine::Application::Get()->GetWindow())
{
}

FramebufferLayer::~FramebufferLayer()
{
}

void FramebufferLayer::OnAttach()
{
	float vertices[] =
	{

		//Positions.			//Texture Coordinates.
	   -0.5f,  0.5f, 0.0f,		0.0f, 1.0f,		// Top LEFT     => 0
		0.5f,  0.5f, 0.0f,		1.0f, 1.0f,		// Top RIGHT    => 1
	   -0.5f, -0.5f, 0.0f,		0.0f, 0.0f,		// Bottom LEFT  => 2
		0.5f, -0.5f, 0.0f,		1.0f, 0.0f		// Bottom RIGHT => 3
	};


	float quadVerts[] =
	{

		//Positions.			//Texture Coordinates.
	   -1.0f,  1.0f, 0.0f,		0.0f, 1.0f,		// Top LEFT     => 0
		1.0f,  1.0f, 0.0f,		1.0f, 1.0f,		// Top RIGHT    => 1
	   -1.0f, -1.0f, 0.0f,		0.0f, 0.0f,		// Bottom LEFT  => 2
		1.0f, -1.0f, 0.0f,		1.0f, 0.0f		// Bottom RIGHT => 3
	};

	unsigned int indices[] =
	{
		0, 2, 3,
		1, 0, 3
	};

	m_texturedQuad = VampEngine::VertexArray::Create();

	VampEngine::BufferLayout layout =
	{
		{VampEngine::BufferDataType::FLOAT3, "positions"},
		{VampEngine::BufferDataType::FLOAT2, "text coords"}
	};

	VampEngine::VertexBuffer* vbo = VampEngine::VertexBuffer::Create(vertices, sizeof(vertices), layout);
	VampEngine::IndexBuffer* ebo  = VampEngine::IndexBuffer::Create(indices, sizeof(indices));

	m_texturedQuad->AddBuffer(vbo);
	m_texturedQuad->SetIndexBuffer(ebo);

	VampEngine::ShaderProps shaderProps("src/Shaders/TexturedQuad.vert", "src/Shaders/TexturedQuad.frag");
	m_texturedQuadShader = VampEngine::Shader::Create(shaderProps);

	VampEngine::Texture2DProps  textureProps("Assets/Checkerboard.jpg");
	m_texture = VampEngine::Texture2D::Create(textureProps);


	m_quad = VampEngine::VertexArray::Create();

	vbo = VampEngine::VertexBuffer::Create(quadVerts, sizeof(quadVerts), layout);
	ebo = VampEngine::IndexBuffer::Create(indices, sizeof(indices));

	m_quad->AddBuffer(vbo);
	m_quad->SetIndexBuffer(ebo);

	VampEngine::ShaderProps processShaderProps("src/Shaders/PostProcess.vert", "src/Shaders/PostProcess.frag");
	m_processShader = VampEngine::Shader::Create(processShaderProps);

	VampEngine::FrameBufferProps frambufferProps(VAMP_FRAMEBUFFER_COLOR | VAMP_FRAMEBUFFER_DEPTH_STENCIL, 
		m_window->GetWidth(), m_window->GetHeight());
	m_framebuffer = VampEngine::FrameBuffer::Create(frambufferProps);

}

void FramebufferLayer::OnDetatch()
{
}

void FramebufferLayer::OnUpdate()
{
	
	m_framebuffer->Bind();

	m_texturedQuad->Bind();
	m_texturedQuadShader->Bind();
	m_texture->Bind();
	VampEngine::RendererCommand::Get()->DrawIndexed(m_texturedQuad);

	m_framebuffer->Unbind();


	m_quad->Bind();
	m_processShader->Bind();
	m_framebuffer->GetColorTexture()->Bind();
	VampEngine::RendererCommand::Get()->DrawIndexed(m_quad);
}

void FramebufferLayer::OnEvent(VampEngine::Event& e)
{
	VampEngine::Dispatcher dispatcher(e);

	dispatcher.Dispatch<VampEngine::WindowResizeEvent>([this](VampEngine::WindowResizeEvent& e)->bool
	{
			m_framebuffer->Update(e.GetWidth(), e.GetHeight());

			return false;
	});
}
