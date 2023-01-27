workspace "LSAP"
    architecture "x64"
    startproject "Sandbox"

    configurations
    {
        "Debug",
        "Release",
        "Dist"
    }
    outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"

    IncludeDir = {}
    IncludeDir["GLFW3"] = "LSAP/vendor/GLFW3/include"
    IncludeDir["glad"] = "LSAP/vendor/glad/include"
    IncludeDir["imGui"] = "LSAP/vendor/imGui"


    group "Dependencies"
        include "LSAP/vendor/GLFW3"
        include "LSAP/vendor/glad"
        include "LSAP/vendor/imGui"
    
    group ""

    project "LSAP"
        location "LSAP"
        kind "StaticLib"
        language "C++"
        cppdialect "C++20"
        staticruntime "on"

        targetdir ("bin/" .. outputdir .. "/%{prj.name}")
        objdir    ("bin-int/" .. outputdir .. "/%{prj.name}")

        pchheader "lspch.h"
        pchsource "LSAP/src/lspch.cpp"

        files
        {
            "%{prj.name}/src/**.h",
            "%{prj.name}/src/**.cpp"
        }

        defines
        {
            "_CRT_SECURE_NO_WARNINGS"
        }
        includedirs
        {
            "%{prj.name}/src",
            "%{IncludeDir.GLFW3}",
            "%{IncludeDir.glad}",
            "%{IncludeDir.imGui}",
            "%{prj.name}/vendor/spdlog/include"
        }
        links
        {
            "GLFW",
            "opengl32.lib",
            "glad",
            "imGui",
            "winmm.lib"
        }

        filter "system:windows"
        systemversion "latest"

        defines
        {
            "LS_PLATFORM_WINDOWS",
            "LS_BUILD_DLL",
            "GLFW_INCLUDE_NONE"
        }

        filter "configurations:Debug"
        defines "LS_DEBUG"
        runtime "Debug"
        symbols "on"

        filter "configurations:Release"
        defines "LS_RELEASE"
        runtime "Release"
        optimize "on"

        filter "configurations:Dist"
        defines "LS_DIST"
        runtime "Release"
        optimize "on"

project "Sandbox"
        location "Sandbox"
        kind "ConsoleApp"
        language "C++"
        cppdialect "C++20"
        staticruntime "on"

        targetdir ("bin/" .. outputdir .. "/%{prj.name}")
        objdir    ("bin-int/" .. outputdir .. "/%{prj.name}")

        files
        {
            "%{prj.name}/src/**.h",
            "%{prj.name}/src/**.cpp"
        }
        
        includedirs
        {
            "LSAP/src",
            "LSAP/vendor/spdlog/include",
            "LSAP/vendor"
        }

        links
        {
            "LSAP"
        }
    
        filter "system:windows"
            systemversion "latest"
    
            defines
            {
                "LS_PLATFORM_WINDOWS"
            }
    
        filter "configurations:Debug"
            defines "LS_DEBUG"
            runtime "Debug"
            symbols "on"
    
        filter "configurations:Release"
            defines "LS_RELEASE"
            runtime "Release"
            optimize "on"
    
        filter "configurations:Dist"
            defines "LS_DIST"
            runtime "Release"
            optimize "on"
