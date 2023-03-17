project "GLFW"
	kind "StaticLib"
	language "C"
	architecture "x86_64"

	targetdir "bin/%{cfg.buildcfg}"
	objdir "bin-int/%{cfg.buildcfg}"

	includedirs { "windowCreation/include/" }

	files
	{
		"windowCreation/include/GLFW/glfw3.h",
		"windowCreation/include/GLFW/glfw3native.h",
		"windowCreation/src/internal.h",
		"windowCreation/src/platform.h",
		"windowCreation/src/mappings.h",
		"windowCreation/src/context.c",
		"windowCreation/src/init.c",
		"windowCreation/src/input.c",
		"windowCreation/src/monitor.c",
		"windowCreation/src/platform.c",
		"windowCreation/src/vulkan.c",
		"windowCreation/src/window.c",
		"windowCreation/src/egl_context.c",
		"windowCreation/src/osmesa_context.c",
		"windowCreation/src/null_platform.h",
		"windowCreation/src/null_joystick.h",
		"windowCreation/src/null_init.c",
		"windowCreation/src/null_monitor.c",
		"windowCreation/src/null_window.c",
		"windowCreation/src/null_joystick.c",
	}

	filter "system:windows"
		systemversion "latest"
		staticruntime "On"

		files
		{
			"windowCreation/src/win32_init.c",
			"windowCreation/src/win32_module.c",
			"windowCreation/src/win32_joystick.c",
			"windowCreation/src/win32_monitor.c",
			"windowCreation/src/win32_time.h",
			"windowCreation/src/win32_time.c",
			"windowCreation/src/win32_thread.h",
			"windowCreation/src/win32_thread.c",
			"windowCreation/src/win32_window.c",
			"windowCreation/src/wgl_context.c",
			"windowCreation/src/egl_context.c",
			"windowCreation/src/osmesa_context.c"
		}

		defines 
		{ 
			"_GLFW_WIN32",
			"_CRT_SECURE_NO_WARNINGS"
		}
	
	filter "configurations:Debug"
		runtime "Debug"
		symbols "on"

	filter "configurations:Release"
		runtime "Release"
		optimize "on"