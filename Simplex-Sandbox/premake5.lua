
-- Test project that will link with the Simplex Game Engine
project "Simplex-Sandbox"
	language "C++"
	cppdialect "C++17"
	kind "ConsoleApp"

	files {
		"src/**.cpp",
		"src/**.h",
		"res/**"
	}

	includedirs {
		"src",
		"%{wks.location}/Simplex/include",
		"%{wks.location}/Simplex/vendor/spdlog/include" -- TODO: should not be a 'visible' dependency
	}

	links {
		"Simplex"
	}

	filter "toolset:not msc"
		links {
			"GLFW",
			"Glad",
			"stb_image",
		}

	filter "system:linux"
		links {
			"GL",
			"dl",
			"m",
			"X11",
			"pthread"
		}

	filter {}

	defines {
		"SPMX_APP"
	}

	targetdir(TARGET_OUTPUT)
	objdir(OBJECT_OUTPUT)