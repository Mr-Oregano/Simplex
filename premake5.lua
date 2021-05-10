
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

	include "Simplex"
	include "Simplex-Sandbox"
