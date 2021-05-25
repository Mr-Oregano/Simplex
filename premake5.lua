
TARGET_OUTPUT = "bin/%{cfg.architecture}-%{cfg.buildcfg}-%{cfg.system}"
OBJECT_OUTPUT = "bin-int/%{cfg.architecture}-%{cfg.buildcfg}-%{cfg.system}"

workspace "Simplex"
	startproject "Simplex-Sandbox"
	architecture "x64"
	staticruntime "on"
	flags "MultiProcessorCompile"

	configurations {
		"Debug",
		"Release",
		"Dist"
	}

	filter "configurations:Debug"
		defines "SMPX_CONFIG_DEBUG"
		optimize "off"
		symbols "on"

	filter "configurations:Release"
		defines "SMPX_CONFIG_RELEASE"
		optimize "on"
		symbols "off"

	filter "configurations:Dist"
		defines "SMPX_CONFIG_DIST"
		optimize "on"
		symbols "off"

	filter "system:windows"
		systemversion "latest"
		defines "SMPX_SYSTEM_WINDOWS"

	filter {}

	include "Simplex"
	include "Simplex-Sandbox"
