project "LSAPAudio"
	location "LSAPAudio"
	kind "StaticLib"
	language "C++"
	cppdialect "C++20"
	staticruntime "on"

	targetdir ("bin/" .. outputdir .. "/%{prj.name}")
	objdir ("bin-int/" .. outputdir .. "/%{prj.name}")

	pchheader "audiopch.h"
	pchsource "src/audiopch.cpp"

	includedirs
	{
		"../LSAP/src"
	}

	files
	{
		"src/**.h",
        "src/**.cpp"
	}

	filter "system:windows"
		systemversion "latest"

		links
		{
			"winmm.lib"
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