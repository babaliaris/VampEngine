#pragma once
#include "VampEngine.h"

class FramebufferLayer : public VampEngine::Layer
{
	public:
		FramebufferLayer();

		virtual ~FramebufferLayer();

		virtual void OnAttach() override;

		virtual void OnDetatch() override;

		virtual void OnUpdate() override;

		virtual void OnEvent(VampEngine::Event& e) override;

	private:

		VampEngine::Window* m_window;

		VampEngine::VertexArray* m_texturedQuad = nullptr;
		VampEngine::VertexArray* m_quad = nullptr;
		VampEngine::Shader* m_texturedQuadShader = nullptr;
		VampEngine::Shader* m_processShader = nullptr;
		VampEngine::Texture2D* m_texture = nullptr;
		VampEngine::FrameBuffer* m_framebuffer = nullptr;
};

