#include "pch.h"
#include "Renderer.h"
#include "VampAssert.h"

namespace VampEngine
{

	Renderer* Renderer::s_Instance = nullptr;


	void Renderer::Create()
	{
		VAMP_ASSERT(s_Instance == nullptr, "Renderer has already been spawn!");
		s_Instance = new Renderer();
	}

	void Renderer::BeginScene()
	{
	}



	void Renderer::EndScene()
	{
	}



	void Renderer::Submit()
	{
	}
}
