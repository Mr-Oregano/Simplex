
group "Vendor"
	include "vendor/glfw"
group ""

-- Simplex Game Engine project
project "Simplex"
	language "C++"
	cppdialect "C++17"
	kind "StaticLib"

	pchheader "sxpch.h"
	pchsource "src/sxpch.cpp"

	files {
		"src/**.cpp",
		"include/**.h"
	}

	excludes "src/Native/**"

	filter "system:windows"
		files {
			"src/Native/Windows/**.cpp",
			"src/Native/Windows/**.h"
		}	

	filter {}

	includedirs {
		"include",

		"vendor/spdlog/include",
		"vendor/glfw/include"
	}

	links {
		"GLFW",
	}

	defines {
		-- Some dependencies may use C std functions which cause warnings in C++17
		-- the following flag will silence these warnings that may be produce.
		"_CRT_SECURE_NO_WARNINGS",

		-- Using the C++17 dialect on the 'fmt' library (used by 'spdlog'')
		-- Will generate several warnings, the following flag will suppress 
		-- these warnings.
		"_SILENCE_CXX17_RESULT_OF_DEPRECATION_WARNING"
	}

	targetdir(TARGET_OUTPUT)
	objdir(OBJECT_OUTPUT)
