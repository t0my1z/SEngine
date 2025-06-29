project "SEngine"

	kind "StaticLib"
	language "C++"
	cppdialect "C++20" 
	staticruntime "on"  

	targetdir ("../bin/" .. outputdir .. "/%{prj.name}") 
	objdir ("../bin-int/" .. outputdir .. "/%{prj.name}") 

	files
	{
		"Source/**.h",
		"Source/**.cpp" 
	}

	includedirs 
	{
		"Source"
	}

	links
	{
		"opengl32.lib"
	}

	filter "system:windows"
		systemversion "10.0.19041.0:latest"

		defines
		{
			"SE_PLATFORM_WINDOWS",
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