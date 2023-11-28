workspace "VampEngine Workspace"
    platforms "x64"
    configurations {"debug", "dist", "release"}
    startproject "Sandbox"

    group "Depedencies"
        include "depedencies/vamptest/projects/VampTest"
        include "depedencies/vampstring/projects/VampString"
    group ""

    include "projects/VampEngine"
    include "projects/Sandbox"
    include "projects/Tests"