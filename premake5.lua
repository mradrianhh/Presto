workspace "Presto"
    architecture "x86_64"
    startproject "Prestissimo"

    configurations
    {
        "Debug",
        "Release",
        "Dist"
    }

outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"

IncludeDir = {}
IncludeDir["GLFW"] = "Presto/vendor/GLFW/include"
IncludeDir["GLAD"] = "Presto/vendor/GLAD/include"
IncludeDir["ImGui"] = "Presto/vendor/imgui"
IncludeDir["glm"] = "Presto/vendor/glm"


include "Presto/vendor/GLFW"
include "Presto/vendor/GLAD"
include "Presto/vendor/imgui"

project "Presto"
    location "Presto"
    kind "StaticLib"
    language "C++"
    cppdialect "C++17"
    staticruntime "off"

    targetdir ("bin/" .. outputdir .. "/%{prj.name}")
    objdir ("bin-int/" .. outputdir .. "/%{prj.name}")

    pchheader "prestopch.h"
    pchsource "Presto/src/prestopch.cpp"

    defines
    {
        "_CRT_SECURE_NO_WARNINGS",
        "GLFW_INCLUDE_NONE"
    }

    files
    {
        "%{prj.name}/src/**.h",
        "%{prj.name}/src/**.cpp"
    }

    includedirs
    {
        "%{prj.name}/src",
        "%{IncludeDir.GLFW}",
        "%{IncludeDir.GLAD}",
        "%{IncludeDir.ImGui}",
        "%{IncludeDir.glm}",
        "%{prj.name}/vendor/spdlog/include"
    }

    links
    {
        "GLFW",
        "Glad",
        "imgui",
        "opengl32.lib",

    }

    filter "system:windows"
        systemversion "latest"

        defines
        {
            "PRESTO_PLATFORM_WINDOWS",
        }

        postbuildcommands
        {
            "{COPYDIR} %{cfg.buildtarget.relpath} ../bin/" .. outputdir .. "/Prestissimo"
        }

    filter "configurations:Debug"
        defines "PRESTO_DEBUG"
        symbols "On"
        runtime "Debug"

    filter "configurations:Release"
        defines "PRESTO_RELEASE"
        optimize "On"
        runtime "Release"

    filter "configurations:Dist"
        defines "PRESTO_DIST"
        optimize "On"
        runtime "Release"

project "Prestissimo"
    location "Prestissimo"
    kind "ConsoleApp"
    language "C++"
    cppdialect "C++17"
    staticruntime "off"

    targetdir ("bin/" .. outputdir .. "/%{prj.name}")
    objdir ("bin-int/" .. outputdir .. "/%{prj.name}")

    files
    {
        "${prj.name}/src/**.h",
        "${prj.name}/src/**.cpp"
    }

    includedirs
    {
        "%{wks.location}/Presto/src",
        "%{wks.location}/Presto/vendor",
        "%{IncludeDir.glm}",
        "%{wks.location}/Presto/vendor/spdlog/include"
    }

    links
    {
        "Presto"
    }

    filter "system:windows"
        systemversion "latest"

        defines
        {
            "PRESTO_PLATFORM_WINDOWS",
        }

    filter "configurations:Debug"
        defines "PRESTO_DEBUG"
        symbols "on"
        runtime "Debug"

    filter "configurations:Release"
        defines "PRESTO_RELEASE"
        optimize "on"
        runtime "Release"

    filter "configurations:Dist"
        defines "PRESTO_DIST"
        optimize "On"
        runtime "Release"