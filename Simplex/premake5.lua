
group "Vendor"
	include "vendor/GLFW"
	include "vendor/Glad"
	include "vendor/stb_image"
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
		"src/**.h",
		"include/**.h"
	}

	excludes "src/Native/**"

	files {
		"src/Native/FileSystem/**.cpp",
		"src/Native/FileSystem/**.h"
	}

	filter "system:windows"
		files {
			"src/Native/Windows/**.cpp",
			"src/Native/Windows/**.h",

			"src/Native/OpenGL/**.cpp",
			"src/Native/OpenGL/**.h"
		}	

	filter "system:linux"
		files {
			"src/Native/Linux/**.cpp",
			"src/Native/Linux/**.h",
			
			"src/Native/OpenGL/**.cpp",
			"src/Native/OpenGL/**.h"			
		}	

	filter {}

	includedirs {
		"include",
		"src",

		"vendor/spdlog/include",
		"vendor/GLFW/include",
		"vendor/Glad/include",
		"vendor/stb_image/include"
	}

	filter "toolset:msc"
		links {
			"GLFW",
			"Glad"
		}

	filter {}

	defines {
		-- This project uses Glad as an OpenGL loader library so it is not necessary for
		-- GLFW to include the OpenGL header.
		"GLFW_INCLUDE_NONE",
		
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
