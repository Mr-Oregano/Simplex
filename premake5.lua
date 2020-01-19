
-- TARGET_OUTPUT : output directory for the project binaries
-- OBJECT_OUTPUT : output directory for the project intermediates
TARGET_OUTPUT = "bin/%{cfg.architecture}-%{cfg.buildcfg}-%{cfg.system}"
OBJECT_OUTPUT = "bin-int/%{cfg.architecture}-%{cfg.buildcfg}-%{cfg.system}"

workspace "Simplex"
	startproject "Simplex-Sandbox"
	architecture "x64"
	staticruntime "on"

	configurations({
	
		"Debug",
		"Release",
		"Dist"

	})

	filter "configurations:Debug"
		optimize "off"
		symbols "on"

	filter "configurations:Release"
		optimize "on"
		symbols "off"

	filter "configurations:Dist"
		optimize "on"
		symbols "off"

	filter "system:windows"
		systemversion "latest"

	filter {}

-- Simplex Game Engine project
project "Simplex"
	location "Simplex"
	language "C++"
	cppdialect "C++17"
	kind "StaticLib"

	files({
	
		"%{prj.location}/src/**.cpp",
		"%{prj.location}/src/**.h"

	})

	includedirs({
	
		"%{prj.location}/src"

	})

	filter "configurations:Debug"
		defines "SMPX_CONFIG_DEBUG"

	filter "configurations:Release"
		defines "SMPX_CONFIG_RELEASE"

	filter "configurations:Dist"
		defines "SMPX_CONFIG_DIST"

	filter "system:windows"
		defines "SMPX_SYSTEM_WINDOWS"

	filter {}

	targetdir(TARGET_OUTPUT)
	objdir(OBJECT_OUTPUT)
	
-- Test project that will link with the Simplex Game Engine
project "Simplex-Sandbox"
	location "Simplex-Sandbox"
	language "C++"
	cppdialect "C++17"
	kind "ConsoleApp"

	files({
	
		"%{prj.location}/src/**.cpp",
		"%{prj.location}/src/**.h"

	})

	includedirs({
	
		"%{prj.location}/src",
		"%{wks.location}/Simplex/src"

	})

	links({
	
		"Simplex"

	})

	targetdir("%{prj.location}/" .. TARGET_OUTPUT)
	objdir("%{prj.location}/" .. OBJECT_OUTPUT)