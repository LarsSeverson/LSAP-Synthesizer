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
    IncludeDir["glm"] = "LSAP/vendor/glm"
    IncludeDir["stb_image"] = "LSAP/vendor/stb_image"
    IncludeDir["LSAPAudio"] = "LSAPAudio"


    group "Dependencies"
        include "LSAP/vendor/GLFW3"
        include "LSAP/vendor/glad"
        include "LSAP/vendor/imGui"
        include "LSAPAudio"
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
            "%{prj.name}/src/**.cpp",
            "%{prj.name}/vendor/glm/glm/**.hpp",
            "%{prj.name}/vendor/glm/glm/**.inl",
            "%{prj.name}/vendor/stb_image/**.h",
            "%{prj.name}/vendor/stb_image/**.cpp"
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
            "%{IncludeDir.glm}",
            "%{prj.name}/vendor/spdlog/include",
            "%{IncludeDir.stb_image}",
            "%{IncludeDir.LSAPAudio}"
        }
        links
        {
            "GLFW",
            "opengl32.lib",
            "glad",
            "imGui"
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
            "LSAP/vendor",
            "%{IncludeDir.glm}",
            "%{IncludeDir.LSAPAudio}/src"
        }

        links
        {
            "LSAP",
            "LSAPAudio"
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
