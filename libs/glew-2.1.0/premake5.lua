project "GLEW"
	kind "StaticLib"
	language "C"
	staticruntime "on"

	targetdir ("bin/" .. outputdir .. "/%{prj.name}")
	objdir ("bin-int/" .. outputdir .. "/%{prj.name}")
	systemversion "latest"

	files
	{
		"include/GL/**.h",
		"src/glew.c",
		"src/glewinfo.c",
		"src/visualinfo.c"
	}

	includedirs
    {
        "include"
	}
	
	filter "system:linux"
		pic "On"

	filter "system:windows"
		defines 
		{ 
			"_CRT_SECURE_NO_WARNINGS"
		}

	filter "configurations:Debug"
		runtime "Debug"
		symbols "on"

	filter "configurations:Release"
		runtime "Release"
		optimize "on"
