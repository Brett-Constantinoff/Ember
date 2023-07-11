local vulkanSdk = os.getenv("VULKAN_SDK")
local vulkanInclude = vulkanSdk.."/include"
local vulkanLib = vulkanSdk.."/lib/vulkan-1.lib"

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
        "Engine/libs/imgui/", 
        "Engine/libs/glad/include/",
        "Engine/libs/stb/",
        "Engine/libs/objLoader/",
	 vulkanInclude
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
        "IMGUI",
        "STB",
        "TINY_OBJ",
 	vulkanLib
    }

    filter "system:windows"
        defines 
        { 
            "_WINDOWS" 
        }
        links
        {
            "OpengL32"
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
        "Engine/libs/imgui/",
        "Engine/libs/stb/",
        "Engine/libs/objLoader",
	 vulkanInclude,
        "Engine"
    }

    files
    {
        "Sandbox/Src/**.cpp",
        "Sandbox/Src/**.h"
    }

    links
    {
        "Engine",
        "GLFW",
        "GLAD",
        "GLM",
        "IMGUI",
        "STB",
        "TINY_OBJ",
	vulkanLib
    }
    
    filter "system:windows"
        links
        {
            "OpenGL32"
        }
    

include "Engine/libs/glfwPremake5.lua"
include "Engine/libs/glmPremake5.lua"
include "Engine/libs/gladPremake5.lua"
include "Engine/libs/imguiPremake5.lua"
include "Engine/libs/stbPremake5.lua"
include "Engine/libs/tinyObjPremake5.lua"
    