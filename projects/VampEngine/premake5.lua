project "VampEngine"
    kind "StaticLib"
    language "C"
    targetdir "%{_WORKING_DIR}/builds/%{cfg.shortname}"
    objdir "%{_WORKING_DIR}/obj/%{prj.name}-%{cfg.shortname}"

    pchheader "VampPCH.h"
    pchsource "src/VampPCH.c"

    files {
        "src/**.h",
        "src/**.c"
    }

    includedirs {
        "src/",
        "%{_WORKING_DIR}/depedencies/vampstring/projects/VampString/src"
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