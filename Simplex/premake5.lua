
-- Simplex Game Engine project
project "Simplex"
	language "C++"
	cppdialect "C++17"
	kind "StaticLib"

	files {
		"src/**.cpp",
		"include/**.h"
	}

	includedirs {
		"include",
		"vendor/spdlog/include"
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
