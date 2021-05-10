
-- Test project that will link with the Simplex Game Engine
project "Simplex-Sandbox"
	language "C++"
	cppdialect "C++17"
	kind "ConsoleApp"

	files {
		"src/**.cpp",
		"src/**.h"
	}

	includedirs {
		"src",
		"%{wks.location}/Simplex/include"
	}

	links {
		"Simplex"
	}

	targetdir("%{prj.location}/" .. TARGET_OUTPUT)
	objdir("%{prj.location}/" .. OBJECT_OUTPUT)