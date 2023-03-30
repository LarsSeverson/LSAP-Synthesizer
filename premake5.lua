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
    IncludeDir["GLFW"] = "LSAP/vendor/GLFW/include"
    IncludeDir["glad"] = "LSAP/vendor/glad/include"
    IncludeDir["imgui"] = "LSAP/vendor/imgui"
    IncludeDir["glm"] = "LSAP/vendor/glm"
    IncludeDir["stb_image"] = "LSAP/vendor/stb_image"
    IncludeDir["LSAPAudio"] = "LSAPAudio"


    group "Dependencies"
        include "LSAP/vendor/GLFW"
        include "LSAP/vendor/glad"
        include "LSAP/vendor/imgui"
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
            "%{IncludeDir.GLFW}",
            "%{IncludeDir.glad}",
            "%{IncludeDir.imgui}",
            "%{IncludeDir.glm}",
            "%{prj.name}/vendor/spdlog/include",
            "%{IncludeDir.stb_image}",
            "%{IncludeDir.LSAPAudio}/src",
            "Sandbox/src/assets"
        }
        links
        {
            "GLFW",
            "opengl32.lib",
            "glad",
            "imgui"
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

project "LSAPAudio"
	location "LSAPAudio"
	kind "StaticLib"
	language "C++"
	cppdialect "C++20"
	staticruntime "on"

	targetdir ("bin/" .. outputdir .. "/%{prj.name}")
	objdir ("bin-int/" .. outputdir .. "/%{prj.name}")

	pchheader "audiopch.h"
	pchsource "LSAPAudio/src/audiopch.cpp"
    
    includedirs
    {
        "LSAP/src",
        "LSAPAudio/src",
        "LSAP/vendor/spdlog/include",
        "%{IncludeDir.imgui}"
    }

    defines
    {
        "LS_PLATFORM_WINDOWS"
    }

	files
	{
		"LSAPAudio/src/**.h",
        "LSAPAudio/src/**.cpp"
	}

	filter "system:windows"
		systemversion "latest"

		links
		{
			"winmm.lib",
            "imgui"
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
