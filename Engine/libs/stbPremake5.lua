project "STB"
	kind "StaticLib"
	language "C"
	architecture "x86_64"

	targetdir "bin/%{cfg.buildcfg}"
	objdir "bin-int/%{cfg.buildcfg}"
    
    includedirs { "stb/" }

	files { "stb/*.cpp", "stb/*.h" }
    
	filter "configurations:Debug"
		runtime "Debug"
		symbols "on"

	filter "configurations:Release"
		runtime "Release"
		optimize "on"