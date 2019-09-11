project "ConsoleApp"
    kind "ConsoleApp"
    language "C++"
    cppdialect "C++11"

    targetdir ("bin/" .. outputdir .. "/%{prj.name}")
    objdir ("bin-int/" .. outputdir .. "/%{prj.name}")
    systemversion "latest"

    files
    {
        "src/log.hpp",
        "src/main.cpp",
    }

    includedirs
    {
        "src",
        "%{IncludeDir.spdlog}",
        "%{IncludeDir.fmt}",
    }

    links 
    { 
        "spdlog",
        "fmt",
    }

    filter "system:linux"
		pic "On"
    
    filter "configurations:Debug"
        runtime "Debug"
        symbols "on"

    filter "configurations:Release"
        runtime "Release"
        optimize "on"
