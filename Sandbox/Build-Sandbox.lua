project "Sandbox"

	kind "ConsoleApp" 
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
		"Source",
		"../SEngine/Source",
		"../SEngine/Vendor"
	}

	links
	{
		"SEngine" 
	}

	filter "system:windows"
		systemversion "10.0.19041.0:latest"

		defines
		{
			"SE_PLATFORM_WINDOWS"
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