#include "pch.h"
#include "Shader.h"

#ifdef VAMP_OPENGL
	#include "Platform/OpenGL/OpenGLShader.h"
#endif

namespace VampEngine
{
	Shader* Shader::Create(const ShaderProps& props)
	{
		#ifdef VAMP_OPENGL
			return new OpenGLShader(props);
		#endif
	}




	ShaderProps::ShaderProps(const std::string vertex_path, const std::string fragment_path)
		: vertex_path(vertex_path), fragment_path(fragment_path)
	{
	}

	ShaderProps::ShaderProps(const std::string vertex_path, const std::string fragment_path, const std::string geometry_path)
		: vertex_path(vertex_path), fragment_path(fragment_path), geometry_path(geometry_path)
	{
	}
}
