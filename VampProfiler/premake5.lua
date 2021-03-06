project "VampProfiler"
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
		"%{wks.location}/VampProfiler/vendor/json/include"
	}