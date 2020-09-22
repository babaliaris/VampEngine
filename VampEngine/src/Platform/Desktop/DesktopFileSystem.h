#pragma once
#include "Core/FileSystem.h"

namespace VampEngine
{
	class DesktopFileSystem : public FileSystem
	{
		//Public Methods.
		public:
			DesktopFileSystem();

		//Public Virtual Methods.
		public:

			//Virtual Deconstructor.
			virtual ~DesktopFileSystem();

			//Virtual Read File.
			virtual std::string ReadFile(const std::string& filepath) const override;

		//Private Members.
		private:

	};
}