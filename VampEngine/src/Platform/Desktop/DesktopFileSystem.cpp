#include "pch.h"
#include "DesktopFileSystem.h"
#include "VampAssert.h"
#include <fstream>
#include <sstream>

namespace VampEngine
{

	DesktopFileSystem::DesktopFileSystem()
	{
	}



	DesktopFileSystem::~DesktopFileSystem()
	{
	}



	std::string DesktopFileSystem::ReadFile(const std::string& filepath) const
	{

		//Open the file.
		std::ifstream file(filepath.c_str());

		//Assert to check if the file failed to open.
		VAMP_ASSERT(file.is_open(), "Failed to open file: %s", filepath.c_str());

		//If the file is opened.
		if (file.is_open())
		{
			//Create a string stream.
			std::stringstream ss;

			//Read the whole file.
			ss << file.rdbuf();

			//Close the file.
			file.close();

			//Return the string.
			return ss.str();
		}

		//Return an empty string.
		return std::string();
	}
}