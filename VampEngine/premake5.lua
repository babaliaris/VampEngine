project "VampEngine"
	kind "StaticLib"
	language "C++"
	targetdir "%{wks.location}/bin/%{prj.name}_%{cfg.shortname}"
	objdir "%{wks.location}/bin-int/%{prj.name}_%{cfg.shortname}"
	
	files {
		"src/**.cpp",
		"src/**.h",
		"premake5.lua"
	}
	
	includedirs{
		"%{wks.location}/VampLogger/src",
		"%{wks.location}/VampAssert/src",
		"%{wks.location}/VampEngine/vendor/glfw-3.3.2/include"
		
	}
	
	--Windows Filter.
	filter "system:windows"
		links {"glfw3", "opengl32"}
		libdirs{
			"%{wks.location}/VampEngine/vendor/glfw-3.3.2/build/src/Release"
		}