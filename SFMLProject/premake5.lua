project "SFMLProject"
    kind "ConsoleApp"
    language "C++"
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
        "src",
        "%{IncludeDir.spdlog}",
    }

    links 
    { 
        "spdlog",
    }

    filter "system:windows"
        defines
        {
            "_WIN32",
            "_WINDOWS",
            "_CRT_SECURE_NO_WARNINGS",
        }
        links 
        { 
            "OpenGL32"
        }
    
    filter "system:linux"
        defines
        {
            "_LINUX",
        }
        links 
        {
            "sfml-graphics",
            "sfml-window",
            "sfml-system",
            "sfml-network",
            "sfml-audio",
        }

    filter "configurations:Debug"
        defines { "DEBUG" }
        symbols "On"

    filter "configurations:Release"
        defines { "RELEASE" }
        optimize "On"