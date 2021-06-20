project "stb_image"
    kind "StaticLib"
    language "C"
    staticruntime "on"
    
    targetdir(TARGET_OUTPUT)
    objdir(OBJECT_OUTPUT)

    files {
        "include/**.h",
        "src/**.cpp"
    }

    includedirs {
        "include"
    }
    
    systemversion "latest"
