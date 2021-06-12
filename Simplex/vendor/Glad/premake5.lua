project "Glad"
    kind "StaticLib"
    language "C"
    staticruntime "on"
    
    targetdir(TARGET_OUTPUT)
    objdir(OBJECT_OUTPUT)

    files {
        "include/glad/glad.h",
        "include/KHR/khrplatform.h",
        "src/glad.c"
    }

    includedirs {
        "include"
    }
    
    systemversion "latest"
