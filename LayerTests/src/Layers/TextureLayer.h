#pragma once
#include "VampEngine.h"

class TextureLayer : public VampEngine::Layer
{
	public:
		TextureLayer();

		virtual ~TextureLayer();

		virtual void OnAttach() override;

		virtual void OnDetatch() override;

		virtual void OnUpdate() override;

		virtual void OnEvent(VampEngine::Event& e) override;

	private:
		VampEngine::VertexArray*	m_vao = nullptr;
		VampEngine::Shader*			m_shader = nullptr;
		VampEngine::Texture2D*		m_texture = nullptr;
};

