workspace "Tilia"
	architecture "x64"
	startproject "Sandbox"

	configurations
	{
		"Debug",
		"Release",
		"Dist"
	}

outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"


--Include directories reletive to root folder (SolutionDir)
IncludeDir = {}
IncludeDir["GLFW"] = "Tilia/vendor/GLFW/include"
IncludeDir["GLAD"] = "Tilia/vendor/GLAD/include"

include "Tilia/vendor/GLFW"
include "Tilia/vendor/GLAD"


project "Tilia"
	location "Tilia"
	kind "SharedLib"
	language "C++"

	targetdir ("bin/" .. outputdir .. "/%{prj.name}")
	objdir ("bin-int/" .. outputdir .. "/%{prj.name}")

	pchheader "tlpch.h"
	pchsource "Tilia/src/tlpch.cpp"

	files
	{
		"%{prj.name}/src/**.h",
		"%{prj.name}/src/**.cpp"
	}

	includedirs
	{
		"%{prj.name}/src",
		"%{prj.name}/vendor/spdlog/include",
		"%{IncludeDir.GLFW}",
		"%{IncludeDir.GLAD}"
	}

	links
	{
		"GLFW",
		"GLAD",
		"opengl32.lib"
	}

	filter "system:windows"
		cppdialect "C++17"
		staticruntime "Off"
		systemversion "latest"

		defines 
		{
			"TL_PLATFORM_WINDOWS",
			"TL_BUILD_DLL",

			"GLFW_INCLUDE_NONE"
		}

		postbuildcommands
		{
			("{COPY} %{cfg.buildtarget.relpath} ../bin/" .. outputdir .. "/Sandbox")
		}

	filter "configurations:Debug"
		defines "TL_DEBUG"
		buildoptions "/MDd"
		symbols "On"

	filter "configurations:Release"
		defines "TL_RELEASE"
		buildoptions "/MD"
		optimize "On"

	filter "configurations:Dist"
		defines "TL_DIST"
		buildoptions "/MD"
		symbols "On"
		
project "Sandbox"
	location "Sandbox"
	kind "ConsoleApp"
	language "C++"

	targetdir ("bin/" .. outputdir .. "/%{prj.name}")
	objdir ("bin-int/" .. outputdir .. "/%{prj.name}")

	files
	{
		"%{prj.name}/src/**.h",
		"%{prj.name}/src/**.cpp"
	}

	includedirs
	{
		"Tilia/vendor/spdlog/include",
		"Tilia/src"
	}

	links 
	{
		"Tilia"
	}

	filter "system:windows"
		cppdialect "C++17"
		staticruntime "On"
		systemversion "latest"

		defines 
		{
			"TL_PLATFORM_WINDOWS"
		}

	filter "configurations:Debug"
		defines "TL_DEBUG"
		buildoptions "/MDd"
		symbols "On"

	filter "configurations:Release"
		defines "TL_RELEASE"
		buildoptions "/MD"
		optimize "On"

	filter "configurations:Dist"
		defines "TL_DIST"
		buildoptions "/MD"
		symbols "On"