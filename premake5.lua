workspace "VampEngine Workspace"
    platforms "x64"
    configurations {"debug", "dist", "release"}
    startproject "Sandbox"

    group "Depedencies"
        include "depedencies/vamptest/projects/VampTest"
        include "depedencies/vampstring/projects/VampString"
        include "depedencies/glfw"
        include "depedencies/glad"
    group ""

    include "projects/VampEngine"
    include "projects/Sandbox"
    include "projects/Tests"