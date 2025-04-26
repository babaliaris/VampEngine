# VampEngine
#### A general-purpose Game Engine made in the C programming language for my [YouTube Course](https://www.youtube.com/watch?v=3ESXRfMvO1M&list=PLDdcp0PqYYgapeHT6Np3HRwaG6ck8sk3d)

## Cloning
```bash
git clone https://github.com/babaliaris/VampEngine.git
```

## Building
You will need [premake](https://premake.github.io/) to build this project.
Run premake5 using the action, depending on which IDE and platform you are working on.
Check the following documentation for [Available Premake5 Actions](https://premake.github.io/docs/Using-Premake)

#### Example in a Linux System
```bash
#Make sure to change inside the root directory of this repo first!!!
premake5 gmake

#Build the workspace using GNU make
make
```

## Run the demo Sandbox application
```bash
./build/debug_x64/sandbox
```
