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
        "Engine/libs/glfw/include/", 
        "Engine/libs/glm/", 
        "Engine/libs/imgui/", 
        "Engine/libs/imgui/examples" ,
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
        "ImGui" ,
        "GLAD"
    }

    filter "system:windows"
        defines 
        { 
            "_WINDOWS" 
        }

include "Engine/libs/glfwPremake5.lua"
include "Engine/libs/glmPremake5.lua"
include "Engine/libs/imguiPremake5.lua"
include "Engine/libs/gladPremake5.lua"

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
        "Engine/libs/glfw/include/", 
        "Engine/libs/glm/", 
        "Engine/libs/imgui/", 
        "Engine/libs/imgui/examples" ,
        "Engine/libs/glad/include/",
        "Engine"
    }

    files
    {
        "Sandbox/Src/**.cpp"
    }

    links
    {
        "Engine"
    }