project "VampEngine"
	kind "StaticLib"
	language "C++"
	targetdir "%{wks.location}/bin/%{prj.name}_%{cfg.shortname}"
	objdir "%{wks.location}/bin-int/%{prj.name}_%{cfg.shortname}"

	--Precompiled Header Configuration.
	pchheader "pch.h"
	pchsource "%{wks.location}/%{prj.name}/src/pch.cpp"
	
	files {
		"src/**.cpp",
		"src/**.h",
		"premake5.lua"
	}
	
	includedirs{
		"%{wks.location}/%{prj.name}/src",
		"%{wks.location}/VampLogger/src",
		"%{wks.location}/VampAssert/src",
		"%{wks.location}/VampProfiler/src",
		"%{wks.location}/VampProfiler/vendor/json/include",
		"%{wks.location}/VampEngine/vendor/glfw-3.3.2/include",
		"%{wks.location}/VampEngine/vendor/glad/include",
		"%{wks.location}/VampEngine/vendor/stb_image/src",
		"%{wks.location}/VampEngine/vendor/glm-9.9.8"
		
	}
	
	links {"Glad", "STBimage"}
	
	--Windows Filter.
	filter "system:windows"
		links {"glfw3", "opengl32"}
		libdirs{
			"%{wks.location}/VampEngine/vendor/glfw-3.3.2/build/src/Release"
		}