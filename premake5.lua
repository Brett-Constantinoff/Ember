workspace "Ember"
    configurations { "Debug", "Release" }
    startproject "Sandbox"
    flags { "MultiProcessorCompile" }

    filter "configurations:Debug"
        defines { "DEBUG", "DEBUG_SHADER" }
        symbols "On"

    filter "configurations:Release"
        defines { "RELEASE" }
        optimize "Speed"
        flags { "LinkTimeOptimization" }

project "Engine"
    location "Engine"
    kind "StaticLib"
    language "C++"
    cppdialect "C++17"
	architecture "x64"

    targetdir "Engine/bin/%{cfg.buildcfg}"
    objdir "Engine/bin-int/%{cfg.buildcfg}"

    includedirs 
    {
        "Engine/libs/windowCreation/include/", 
        "Engine/libs/math/", 
        "Engine/libs/myImgui/", 
        "Engine/libs/glad/include/"
    }
    
    files 
    { 
        "Engine/src/**.cpp",
        "Engine/src/**.h"
    }

    links 
    { 
        "GLFW", 
        "GLM", 
        "GLAD",
        "OpenGL32"
    }

    filter "system:windows"
        defines 
        { 
            "_WINDOWS" 
        }

project "Sandbox"
    location "Sandbox"
    kind "ConsoleApp"
    language "C++"
    cppdialect "C++17"
	architecture "x64"

    targetdir "Sandbox/bin/%{cfg.buildcfg}"
    objdir "Sandbox/bin-int/%{cfg.buildcfg}"

    includedirs
    {
        "Engine/libs/windowCreation/include/", 
        "Engine/libs/math/", 
        "Engine/libs/glad/include/",
        "Engine"
    }

    files
    {
        "Sandbox/Src/**.cpp"
    }

    links
    {
        "Engine",
        "OpenGL32"
    }

include "Engine/libs/glfwPremake5.lua"
include "Engine/libs/glmPremake5.lua"
include "Engine/libs/gladPremake5.lua"
    