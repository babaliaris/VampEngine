workspace "VampEngine Workspace"
    platforms "x64"
    configurations {"debug", "dist", "release"}
    startproject "Sandbox"

    group "Depedencies"
        include "depedencies/vamptest/projects/VampTest"
        include "depedencies/glfw"
        include "depedencies/glad"
        include "depedencies/sds"
    group ""

    include "projects/VampEngine"
    include "projects/Sandbox"
    include "projects/Tests"