#pragma once
#include "Renderer/Shader.h"

namespace VampEngine
{
	class OpenGLShader : public Shader
	{
		//Public Methods.
		public:
			OpenGLShader(const ShaderProps& props);

		//Public Virtual Methods.
		public:

			//Virtual Deconstructor.
			virtual ~OpenGLShader();

			//Bind And Unbind.
			virtual void Bind()		const override;
			virtual void Unbind()	const override;

			//Get Name.
			virtual std::string GetName() const override;


		//Private Methods.
		private:

			//Read File.
			std::string ReadFile(const std::string& filepath);

			//Compile Shader.
			unsigned int CompileShader(unsigned int type, const std::string& source);

		//Private Members.
		private:
			ShaderProps m_props;
			unsigned int m_id;

	};
}