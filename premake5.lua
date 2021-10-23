workspace "Presto"
    architecture "x64"
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

include "Presto/vendor/GLFW"

project "Presto"
    location "Presto"
    kind "SharedLib"
    staticruntime "On"
    language "C++"

    targetdir ("bin/" .. outputdir .. "/%{prj.name}")
    objdir ("bin-int/" .. outputdir .. "/%{prj.name}")

    pchheader "prestopch.h"
    pchsource "Presto/src/prestopch.cpp"

    defines
    {
        "_CRT_SECURE_NO_WARNINGS"
    }

    files
    {
        "%{prj.name}/src/**.h",
        "%{prj.name}/src/**.cpp"
    }

    includedirs
    {
        "%{prj.name}/src",
        "%{IncludeDir.GLFW}"
    }

    links
    {
        "GLFW",
        "opengl32.lib"
    }

    filter "system:windows"
        systemversion "latest"

        defines
        {
            "PRESTO_PLATFORM_WINDOWS",
            "PRESTO_BUILD_DLL"
        }

        postbuildcommands
        {
            "{COPYDIR} %{cfg.buildtarget.relpath} ../bin/" .. outputdir .. "/Prestissimo"
        }

    filter "configurations:Debug"
        defines "PRESTO_DEBUG"
        symbols "On"

    filter "configurations:Release"
        defines "PRESTO_RELEASE"
        optimize "On"

    filter "configurations:Dist"
        defines "PRESTO_DIST"
        optimize "On"

project "Prestissimo"
    location "Prestissimo"
    kind "ConsoleApp"
    language "C++"

    targetdir ("bin/" .. outputdir .. "/%{prj.name}")
    objdir ("bin-int/" .. outputdir .. "/%{prj.name}")

    files
    {
        "${prj.name}/src/**.h",
        "${prj.name}/src/**.cpp"
    }

    includedirs
    {
        "Presto/src",
    }

    links
    {
        "Presto"
    }

    filter "system:windows"
        cppdialect "C++17"
        staticruntime "On"
        systemversion "latest"

        defines
        {
            "PRESTO_PLATFORM_WINDOWS",
        }

    filter "configurations:Debug"
        defines "PRESTO_DEBUG"
        symbols "On"

    filter "configurations:Release"
        defines "PRESTO_RELEASE"
        optimize "On"

    filter "configurations:Dist"
        defines "PRESTO_DIST"
        optimize "On"