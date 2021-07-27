# Simplex Game Engine
The *Simplex Game Engine* is a multi-platform game development environment allowing you to  create and distribute both 3D and 2D games. Providing several tools and environments you can design and create fast single or multiplayer games, simulate real-time physics and lighting, use various post-processing effects, particle systems and more.

**NOTE:** This project is still in development, not all features may be yet available (although they are planned).

## Usage
The *Simplex Game Engine* is currently being built as a static library which you can use to link to any desired C++ project. Include files are provided in the `src/` directory of the *Simplex Game Engine*.

## Building
**IMPORTANT!!!** The *Simplex Game Engine* project uses most 3rd party dependencies as git submodules. Make sure you clone this repository using `git clone --recursive <url>` to ensure that all dependencies are downloaded along with the project.

This project uses [premake](https://premake.github.io/) version 5 to build project files with necessary environment configurations. To build the project files for your development environment of choice, simply download the premake5.exe and run `premake5 <environment>` on the same directory containing the `premake5.lua` file. "\<environment\>" is your selected environment. You can view any possible options from the `premake5 help` menu. 

After premake has generated the project files, there will be a "Sandbox" testing application for you to build and run.

## Dependencies
The following is a list of 3rd party dependencies used (or will be used) by the *Simplex Game Engine*:

 - [GLFW](https://gitlab.com/Sympleque/glfw)
 - [Glad](https://glad.dav1d.de/)
 - [Spdlog](https://github.com/gabime/spdlog)
 - [ImGUI](https://gitlab.com/Sympleque/imgui)
 - [glm](https://github.com/g-truc/glm)
 - [stb](https://github.com/nothings/stb)
 - [openal-soft](https://gitlab.com/Sympleque/openal-soft)
 - [dr_wav](https://github.com/mackron/dr_libs/blob/master/dr_wav.h)
