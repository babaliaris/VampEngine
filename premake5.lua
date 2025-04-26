_VAMP_OBJ_DIR   = "obj"
_VAMP_BUILD_DIR = "build"

workspace "VampEngineWS"
    configurations {"debug", "release", "dist"}
    platforms "x64"

    -- Include our core projects.
    include "Projects/VampEngine/vamp_engine.lua"
    include "Projects/Sandbox/sandbox.lua"
