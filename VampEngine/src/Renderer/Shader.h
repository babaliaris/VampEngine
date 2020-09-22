#pragma once
#include <string>

namespace VampEngine
{

	//Shader Properties.
	struct ShaderProps
	{
		std::string vertex_path;
		std::string fragment_path;
		std::string geometry_path;

		ShaderProps(const std::string vertex_path, const std::string fragment_path);

		ShaderProps(const std::string vertex_path,
					const std::string fragment_path,
					const std::string geometry_path);
	};


	class Shader
	{
		//Public Static Methods.
		public:
			static Shader* Create(const ShaderProps& props);

		//Public Virtual Methods.
		public:

			//Virtual Deconstructor.
			virtual ~Shader() = default;

			//Bind And Unbind.
			virtual void Bind()		const = 0;
			virtual void Unbind()	const = 0;

			//Get Name.
			virtual std::string GetName() const = 0;
	};
}