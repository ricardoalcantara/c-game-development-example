project "bullet"
    kind "StaticLib"
    language "C++"
    staticruntime "on"
    cppdialect "C++11"

    targetdir ("bin/" .. outputdir .. "/%{prj.name}")
    objdir ("bin-int/" .. outputdir .. "/%{prj.name}")
    systemversion "latest"

    files
    {
        "src/**.h",
        "src/**.cpp",
    }

    includedirs
    {
        "src"
    }

    filter "system:linux"
		pic "On"
    
    filter "configurations:Debug"
        runtime "Debug"
        symbols "on"

    filter "configurations:Release"
        runtime "Release"
        optimize "on"
