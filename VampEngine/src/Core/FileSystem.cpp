#include "pch.h"
#include "FileSystem.h"

//Include Desktop File System.
#if (defined VAMP_WINDOWS || defined VAMP_LINUX || defined VAMP_MACOS)
	#include "Platform/Desktop/DesktopFileSystem.h"
#endif


namespace VampEngine
{
	FileSystem* FileSystem::s_Instance = nullptr;

	void FileSystem::Create()
	{

		//Create a new Desktop File System.
		#if (defined VAMP_WINDOWS || defined VAMP_LINUX || defined VAMP_MACOS)
			s_Instance = new DesktopFileSystem();
		#endif
	}
}