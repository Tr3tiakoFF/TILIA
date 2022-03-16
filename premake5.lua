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
IncludeDir["ImGui"] = "Tilia/vendor/imgui"
IncludeDir["GLM"] = "Tilia/vendor/glm"

include "Tilia/vendor/GLFW"
include "Tilia/vendor/GLAD"
include "Tilia/vendor/imgui"


project "Tilia"
	location "Tilia"
	kind "StaticLib"
	language "C++"
	staticruntime "on"

	targetdir ("bin/" .. outputdir .. "/%{prj.name}")
	objdir ("bin-int/" .. outputdir .. "/%{prj.name}")

	pchheader "tlpch.h"
	pchsource "Tilia/src/tlpch.cpp"

	files
	{
		"%{prj.name}/src/**.h",
		"%{prj.name}/src/**.cpp",
		"%{prj.name}/vendor/glm/glm/**.hpp",
		"%{prj.name}/vendor/glm/glm/**.inl"
	}

	defines
	{
		"_CRT_SECURE_NO_WARNINGS"
	}

	includedirs
	{
		"%{prj.name}/src",
		"%{prj.name}/vendor/spdlog/include",
		"%{IncludeDir.GLFW}",
		"%{IncludeDir.GLAD}",
		"%{IncludeDir.ImGui}",
		"%{IncludeDir.GLM}"
	}

	links
	{
		"GLFW",
		"GLAD",
		"ImGui",
		"opengl32.lib"
	}


	filter "system:windows"
		cppdialect "C++17"
		systemversion "latest"

		defines 
		{
			"TL_PLATFORM_WINDOWS",
			"TL_BUILD_DLL",

			"GLFW_INCLUDE_NONE"
		}

	filter "configurations:Debug"
		defines "TL_DEBUG"
		runtime "Debug"
		symbols "on"

	filter "configurations:Release"
		defines "TL_RELEASE"
		runtime "Release"
		optimize "on"

	filter "configurations:Dist"
		defines "TL_DIST"
		runtime "Release"
		optimize "on"
		
project "Sandbox"
	location "Sandbox"
	kind "ConsoleApp"
	language "C++"
	staticruntime "on"

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
		"Tilia/src",
		"Tilia/vendor",
		"%{IncludeDir.GLM}"
	}

	links 
	{
		"Tilia"
	}

	filter "system:windows"
		cppdialect "C++17"
		systemversion "latest"

		defines 
		{
			"TL_PLATFORM_WINDOWS"
		}

	filter "configurations:Debug"
		defines "TL_DEBUG"
		runtime "Debug"
		symbols "on"

	filter "configurations:Release"
		defines "TL_RELEASE"
		runtime "Release"
		optimize "on"

	filter "configurations:Dist"
		defines "TL_DIST"
		runtime "Release"
		optimize "on"