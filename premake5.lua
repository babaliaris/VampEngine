workspace "VampEngine Workspace"
    platforms "x64"
    configurations {"debug", "dist", "release"}
    startproject "Sandbox"

    group "Depedencies"
    group ""

    include "projects/VampEngine"
    include "projects/Sandbox"