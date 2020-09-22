#include "pch.h"
#include "OpenGLShader.h"
#include "OpenGLError.h"
#include "VampAssert.h"
#include "Core/FileSystem.h"
#include <glad/glad.h>
#include <memory>
#include <sstream>



VampEngine::OpenGLShader::OpenGLShader(const ShaderProps& props)
	: m_props(props), m_id(0)
{

	//Compile Vertex & Fragment Shaders.
	unsigned int vert = this->CompileShader(GL_VERTEX_SHADER, this->ReadFile(m_props.vertex_path));
	unsigned int frag = this->CompileShader(GL_FRAGMENT_SHADER, this->ReadFile(m_props.fragment_path));

	//Compile Geometry Shader If Specified.
	unsigned int geo  = 0;
	if (!m_props.geometry_path.empty())
		geo = this->CompileShader(GL_GEOMETRY_SHADER, this->ReadFile(m_props.geometry_path));


	//Create the program.
	VAMP_GLCALL(m_id = glCreateProgram());

	//Attach Vertex And Fragment Shaders.
	VAMP_GLCALL(glAttachShader(m_id, vert));
	VAMP_GLCALL(glAttachShader(m_id, frag));

	//Attach Geometry Shader.
	if (geo > 0)
	{
		VAMP_GLCALL(glAttachShader(m_id, geo));
	}

	//Link And Validate Program.
	VAMP_GLCALL(glLinkProgram(m_id));
	VAMP_GLCALL(glValidateProgram(m_id));

	//Check Link Status.
	int success;
	VAMP_GLCALL(glGetProgramiv(m_id, GL_LINK_STATUS, &success));
	if (!success)
	{
		//Get the Info log Length.
		int log_length;
		VAMP_GLCALL(glGetProgramiv(m_id, GL_INFO_LOG_LENGTH, &log_length));

		//Create a char array.
		std::unique_ptr<char> message = std::make_unique<char>(log_length);

		//Get the message.
		VAMP_GLCALL(glGetProgramInfoLog(m_id, log_length, NULL, message.get()));

		//Assert the error.
		VAMP_ASSERT(success, "[Shader Link Error] => %s", message.get());
	}

	//Delete Vertex and Fragment Shaders.
	VAMP_GLCALL(glDeleteShader(vert));
	VAMP_GLCALL(glDeleteShader(frag));

	//Delete Geometry Shader.
	if (geo > 0)
	{
		VAMP_GLCALL(glDeleteShader(geo));
	}
}




VampEngine::OpenGLShader::~OpenGLShader()
{
	VAMP_GLCALL(glDeleteProgram(m_id));
}




void VampEngine::OpenGLShader::Bind() const
{
	VAMP_GLCALL(glUseProgram(m_id));
}




void VampEngine::OpenGLShader::Unbind() const
{
	VAMP_GLCALL(glUseProgram(0));
}




std::string VampEngine::OpenGLShader::GetName() const
{
	std::stringstream ss;

	size_t start_of_vert = (m_props.vertex_path.find_last_of("/") == std::string::npos) ?
		0 : m_props.vertex_path.find_last_of("/") + 1;

	size_t start_of_frag = (m_props.fragment_path.find_last_of("/") == std::string::npos) ?
		0 : m_props.fragment_path.find_last_of("/") + 1;

	size_t start_of_geo = (m_props.geometry_path.find_last_of("/") == std::string::npos) ?
		0 : m_props.geometry_path.find_last_of("/") + 1;

	std::string vert_name = m_props.vertex_path.substr(start_of_vert, m_props.vertex_path.length());
	std::string frag_name = m_props.fragment_path.substr(start_of_frag, m_props.fragment_path.length());
	std::string geo_name  = m_props.geometry_path.substr(start_of_geo, m_props.geometry_path.length());

	size_t end_of_vert = (vert_name.find_last_of(".") == std::string::npos) ?
		vert_name.length() : vert_name.find_last_of(".");

	size_t end_of_frag = (frag_name.find_last_of(".") == std::string::npos) ?
		frag_name.length() : frag_name.find_last_of(".");

	size_t end_of_geo = (geo_name.find_last_of(".") == std::string::npos) ?
		geo_name.length() : geo_name.find_last_of(".");

	vert_name = vert_name.substr(0, end_of_vert);
	frag_name = frag_name.substr(0, end_of_frag);
	geo_name  = geo_name.substr(0, end_of_geo);

	if (geo_name.empty())
		ss << vert_name << "_" << frag_name;

	else
		ss << vert_name << "_" << frag_name << "_" << geo_name;


	return ss.str();
}





std::string VampEngine::OpenGLShader::ReadFile(const std::string& filepath)
{
	return FileSystem::Get()->ReadFile(filepath);
}





unsigned int VampEngine::OpenGLShader::CompileShader(unsigned int type, const std::string& source)
{

	//----------Some Variables----------//
	unsigned int shader = 0;
	const char* src		= source.c_str();
	//----------Some Variables----------//

	//Create the shader.
	VAMP_GLCALL(shader = glCreateShader(type));

	//Copy the shader Source code.
	VAMP_GLCALL(glShaderSource(shader, 1, &src, NULL));

	//Compile the shader.
	VAMP_GLCALL(glCompileShader(shader));

	//Check Link Status.
	int success;
	VAMP_GLCALL(glGetShaderiv(shader, GL_COMPILE_STATUS, &success));
	if (!success)
	{
		//Get the Info log Length.
		int log_length;
		VAMP_GLCALL(glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &log_length));

		//Create a char array.
		std::unique_ptr<char> message = std::make_unique<char>(log_length);

		//Get the message.
		VAMP_GLCALL(glGetShaderInfoLog(shader, log_length, NULL, message.get()));

		//Assert the error.
		VAMP_ASSERT(success, "[Shader Compile Error] => %s", message.get());

		//Return 0.
		return 0;
	}

	return shader;
}
