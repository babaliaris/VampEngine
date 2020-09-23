#include "pch.h"
#include "OpenGLRendererCommand.h"
#include "OpenGLError.h"
#include "Core/Window.h"
#include <glad/glad.h>

VampEngine::OpenGLRendererCommand::OpenGLRendererCommand()
{
}



VampEngine::OpenGLRendererCommand::~OpenGLRendererCommand()
{
}




void VampEngine::OpenGLRendererCommand::Init(Window* window) const
{

	//Get the Proc Address Function.
	void* proc = window->GetProcAddress();

	//Initialize Glad.
	int gladSuccess = gladLoadGLLoader((GLADloadproc)proc);
	VAMP_ASSERT(gladSuccess, "GLAD failed to be initialized!");

}



void VampEngine::OpenGLRendererCommand::SetClearColor(const glm::vec4& color) const
{
	VAMP_GLCALL(glClearColor(color.r, color.g, color.b, color.a));
}



void VampEngine::OpenGLRendererCommand::Clear() const
{
	VAMP_GLCALL(glClear(GL_COLOR_BUFFER_BIT));
}




void VampEngine::OpenGLRendererCommand::SetViewport(int x, int y, unsigned int width, unsigned int height) const
{
	VAMP_GLCALL(glViewport(x, y, width, height));
}



void VampEngine::OpenGLRendererCommand::DrawIndexed(VertexArray* vao) const
{
	vao->Bind();
	VAMP_GLCALL(glDrawElements(GL_TRIANGLES, vao->GetIndexBuffer()->GetCount(), GL_UNSIGNED_INT, NULL));
	vao->Unbind();
}
