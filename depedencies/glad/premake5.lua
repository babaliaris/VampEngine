project "GLAD"
    kind "StaticLib"
    language "C"
    targetdir "%{_WORKING_DIR}/builds/%{cfg.shortname}"
    objdir "%{_WORKING_DIR}/obj/%{prj.name}-%{cfg.shortname}"

    files {
        "**.h",
        "**.c"
    }

    includedirs {
        "include",
    }

    filter "configurations:debug"
        defines "VAMP_DEBUG"
        optimize "Off"
        symbols "On"

    filter "configurations:dist"
        defines "VAMP_DIST"
        optimize "On"
        symbols "Off"

    filter "configurations:release"
        defines "VAMP_RELEASE"
        optimize "On"
        symbols "Off"