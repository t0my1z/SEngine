IncludeDir = {}
IncludeDir["GLFW"]		=	"Vendor/GLFW/include"
IncludeDir["Glad"]		=	"Vendor/Glad/include"
IncludeDir["Vulkan"]	=	"Vendor/Vulkan/Include"
IncludeDir["stb_image"] =	"Vendor/stb_image"

include "Vendor/GLFW"
include "Vendor/Glad/Build-Glad.lua"

project "SEngine"

	kind "StaticLib"
	language "C++"
	cppdialect "C++20" 
	staticruntime "on"  

	targetdir ("../bin/" .. outputdir .. "/%{prj.name}") 
	objdir ("../bin-int/" .. outputdir .. "/%{prj.name}") 

	pchheader "sepch.h"
	pchsource "Source/sepch.cpp" 

	files
	{
		"Source/**.h",
		"Source/**.cpp",
		"%{IncludeDir.stb_image}/**.h",
		"%{IncludeDir.stb_image}/**.cpp"
	}

	includedirs 
	{
		"Source",
		"%{IncludeDir.GLFW}",
		"%{IncludeDir.Glad}",
		"%{IncludeDir.Vulkan}",
		"%{IncludeDir.stb_image}"
	}

	libdirs
	{
		"Vendor/Vulkan/Lib"
	}

	links
	{
		"GLFW",
		"Glad",
		"vulkan-1",
		"opengl32.lib"
	}

	filter "system:windows"
		systemversion "10.0.19041.0:latest"

		defines
		{
			"SE_PLATFORM_WINDOWS",
			"SE_BUILD_DLL",
			"GLFW_INCLUDE_NONE"
		}

	filter "configurations:Debug"
		defines "SE_DEBUG"
		runtime "Debug" 
		symbols "on"

	filter "configurations:Release"
		defines "SE_RELEASE" 
		runtime "Release"
		optimize "on" 

	filter "configurations:Dist"
		defines "SE_DIST" 
		runtime "Release"
		optimize "on" 