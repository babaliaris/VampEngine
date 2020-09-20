workspace "VampEngine"
	architecture "x64"
	platforms "x64"
	configurations {"Debug", "Release", "Dist"}
	startproject "Sandbox"
	
	--Windows Filter for ALL Projects.
	filter "system:windows"
		defines "VAMP_WINDOWS"
		defines "_CRT_SECURE_NO_WARNINGS"
		
	--Debug Filter for ALL Projects.
	filter {}
	filter "configurations:Debug"
		defines "VAMP_DEBUG"
	
	--Include The All The Projects.
	include "VampEngine"
	include "Sandbox"
	
	--Include All The Depedency Projects.
	group "Depedencies"
		include "VampLogger"
		include "VampTest"
	group ""