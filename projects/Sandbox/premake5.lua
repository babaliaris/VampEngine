project "Sandbox"
    targetname "sandbox"
    kind "ConsoleApp"
    language "C"
    targetdir "%{_WORKING_DIR}/builds/%{cfg.shortname}"
    objdir "%{_WORKING_DIR}/obj/%{prj.name}-%{cfg.shortname}"

    files {
        "src/**.h",
        "src/**.c"
    }

    includedirs {
        "src/",
        "%{_WORKING_DIR}/projects/VampEngine/src",
        "%{_WORKING_DIR}/depedencies/sds",
        
    }

    links {
        "VampEngine",
        "GLFW",
        "GLAD",
        "SDS"
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

    filter {}
    filter "system:linux"
        links {"GL", "m"}