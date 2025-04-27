project "Sandbox"
    kind "ConsoleApp"
    language "C"
    cdialect "C99"
    targetname "sandbox"
    objdir ("%{_WORKING_DIR}/%{_VAMP_OBJ_DIR}/%{cfg.shortname}_%{prj.name}")
    targetdir ("%{_WORKING_DIR}/%{_VAMP_BUILD_DIR}/%{cfg.shortname}")

    files {
        "src/**.h",
        "src/**.c"
    }

    includedirs {
        "%{_WORKING_DIR}/Projects/VampEngine/include"
    }

    links {
        "VampEngine"
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

    filter {"configurations:debug"}
        symbols "On"
        optimize "Off"

    filter {"configurations:release"}
        symbols "Off"
        optimize "On"

    filter {"configurations:dist"}
        symbols "Off"
        optimize "On"
