project "Glad"
	kind "StaticLib"
	language "C++"
	targetdir "%{wks.location}/bin/%{prj.name}_%{cfg.shortname}"
	objdir "%{wks.location}/bin-int/%{prj.name}_%{cfg.shortname}"
	
	files {
		"src/**.c",
		"src/**.h",
		"premake5.lua"
	}
	
	includedirs{
		"include"
	}