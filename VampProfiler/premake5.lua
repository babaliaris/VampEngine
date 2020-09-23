project "VampProfiler"
	kind "ConsoleApp"
	language "C++"
	targetdir "%{wks.location}/bin/%{prj.name}_%{cfg.shortname}"
	objdir "%{wks.location}/bin-int/%{prj.name}_%{cfg.shortname}"
	
	files {
		"%{wks.location}/%{prj.name}/src",
		"src/**.cpp",
		"src/**.h",
		"premake5.lua"
	}

	includedirs{
		"%{wks.location}/VampProfiler/vendor/json/include"
	}