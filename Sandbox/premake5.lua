project "Sandbox"
	kind "ConsoleApp"
	language "C++"
	targetdir "%{wks.location}/bin/%{prj.name}_%{cfg.shortname}"
	objdir "%{wks.location}/bin-int/%{prj.name}_%{cfg.shortname}"
	
	files {
		"src/**.cpp",
		"src/**.h",
		"premake5.lua"
	}

	includedirs{
		"%{wks.location}/%{prj.name}/src",
		"%{wks.location}/VampEngine/src",
		"%{wks.location}/VampAssert/src",
		"%{wks.location}/VampLogger/src",
		"%{wks.location}/VampProfiler/src",
		"%{wks.location}/VampProfiler/vendor/json/include",
		"%{wks.location}/VampEngine/vendor/glm-9.9.8"
	}
	
	links "VampEngine"