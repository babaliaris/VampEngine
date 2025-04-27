project "VampEngine"
    kind "SharedLib"
    language "C"
    cdialect "C99"
    objdir ("%{_WORKING_DIR}/%{_VAMP_OBJ_DIR}/%{cfg.shortname}_%{prj.name}")
    targetdir ("%{_WORKING_DIR}/%{_VAMP_BUILD_DIR}/%{cfg.shortname}")

    files {
        "src/**.c",
        "include/**.h"
    }

    includedirs {
        "include"
    }

    warnings "Extra"

    -- Predefined macros for each major PC Platform --
    filter {"system:linux"}
        defines {"VAMP_LINUX"}

    filter {"system:windows"}
        defines {"VAMP_WINDOWS"}

    filter {"system:macosx"}
        defines {"VAMP_MACOS"}
    -- Predefined macros for each major PC Platform --


    filter {} --Clean all filters.


    -- Configuration based options for EVERY platform --
    filter {"configurations:debug"}
        symbols "On"
        optimize "Off"

    filter {"configurations:release"}
        symbols "Off"
        optimize "On"

    filter {"configurations:dist"}
        symbols "Off"
        optimize "On"
    -- Configuration based options for EVERY platform --
