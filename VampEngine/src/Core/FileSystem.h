#pragma once
#include <string>

namespace VampEngine
{
	class FileSystem
	{
		friend class Application;

		//Public Static Methods.
		public:

			inline static FileSystem* const Get() { return s_Instance; }

		//Public Virtual Methods.
		public:

			//Virtual Deconstructor.
			virtual ~FileSystem() = default;

			//Virtual Read File.
			virtual std::string ReadFile(const std::string& filepath) const = 0;

		//Private Methods.
		private:
			static void Create();

		//private Members.
		private:
			static FileSystem* s_Instance;

	};
}