# VampEngine

## Requirments For Building
* Latest [premake5](https://premake.github.io/) **(optional: added in your *PATH*)**
* Latest [cmake](https://cmake.org/) . **YOU MUST** add *cmake* to your *PATH*, since *premake5* will use it automatically!!!

From now and on, I will use **REPO_DIR** to point to the cloned local repository of this project.

## How To Compile And Build On Windows.
1. Run `premake5 <target>` to generate the project files : for example `premake5 vs2019` (generate files for visual studio).
2. Go into `REPO_DIR/VampEngine/vendor/glfw-3.3.2/build` and build GLFW. Depending on your system configuration, cmake should
   have already generated the required files for your building tools.
3. You can now open the `REPO_DIR/VampEngine` project (again depending of the files that premake generated, for example
   for visual studio you will have a `REPO_DIR/VampEngine.sln` file.) and build the solution/workspace.
   
   
 ## How To Compile And Build On Linux.
 Currently not supported.
