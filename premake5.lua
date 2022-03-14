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
	kind "SharedLib"
	language "C++"
	staticruntime "Off"

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

		postbuildcommands
		{
			("{COPY} %{cfg.buildtarget.relpath} ../bin/" .. outputdir .. "/Sandbox")
		}

	filter "configurations:Debug"
		defines "TL_DEBUG"
		runtime "Debug"
		symbols "On"

	filter "configurations:Release"
		defines "TL_RELEASE"
		runtime "Release"
		optimize "On"

	filter "configurations:Dist"
		defines "TL_DIST"
		runtime "Release"
		symbols "On"
		
project "Sandbox"
	location "Sandbox"
	kind "ConsoleApp"
	language "C++"
	staticruntime "Off"

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
		"%{IncludeDir.GLM}",
		"Tilia/vendor"
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
		symbols "On"

	filter "configurations:Release"
		defines "TL_RELEASE"
		runtime "Release"
		optimize "On"

	filter "configurations:Dist"
		defines "TL_DIST"
		runtime "Release"
		symbols "On"