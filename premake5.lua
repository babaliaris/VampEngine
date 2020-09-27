os.execute("cmake -S VampEngine/vendor/glfw-3.3.2 -B VampEngine/vendor/glfw-3.3.2/build")


workspace "VampEngine"
	architecture "x64"
	platforms "x64"
	configurations {"Debug", "Release", "Dist"}
	startproject "LayerTests"
	
	--To Be Abstracted.
	defines "VAMP_OPENGL"
	
	--Windows Filter for ALL Projects.
	filter "system:windows"
		defines "VAMP_WINDOWS"
		defines "_CRT_SECURE_NO_WARNINGS"
		
	--Debug Filter for ALL Projects.
	filter {}
	filter "configurations:Debug"
		defines "VAMP_DEBUG"
		defines "VAMP_ENABLE_ASSERTS"
		symbols "On"
		
	--Release Filter for ALL Projects.
	filter {}
	filter "configurations:Release"
		defines "VAMP_ENABLE_PROFILER"
		optimize "On"
		
	--Distribution Filter for ALL Projects.
	filter {}
	filter "configurations:Dist"
		optimize "On"
		
	
	--Include The All The Projects.
	include "VampEngine"
	include "Sandbox"
	include "LayerTests"
	include "UnitTests"
	
	--Include All The Depedency Projects.
	group "Depedencies"
		include "VampLogger"
		include "VampTest"
		include "VampAssert"
		include "VampEngine/vendor/glad"
		include "VampEngine/vendor/stb_image"
		include "VampProfiler"
	group ""