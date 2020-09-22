#include "pch.h"
#include "OpenGLRendererCommand.h"
#include "OpenGLError.h"
#include <glad/glad.h>

VampEngine::OpenGLRendererCommand::OpenGLRendererCommand()
{
}



VampEngine::OpenGLRendererCommand::~OpenGLRendererCommand()
{
}



void VampEngine::OpenGLRendererCommand::SetClearColor(const glm::vec4& color) const
{
	VAMP_GLCALL(glClearColor(color.r, color.g, color.b, color.a));
}



void VampEngine::OpenGLRendererCommand::Clear() const
{
	VAMP_GLCALL(glClear(GL_COLOR_BUFFER_BIT));
}



void VampEngine::OpenGLRendererCommand::DrawIndexed(VertexArray* vao) const
{
	vao->Bind();
	VAMP_GLCALL(glDrawElements(GL_TRIANGLES, vao->GetIndexBuffer()->GetCount(), GL_UNSIGNED_INT, NULL));
	vao->Unbind();
}
