project "spdlog"
    kind "StaticLib"
    language "C++"
    staticruntime "on"
    cppdialect "C++11"

    targetdir ("bin/" .. outputdir .. "/%{prj.name}")
    objdir ("bin-int/" .. outputdir .. "/%{prj.name}")
    systemversion "latest"

    files
    {
        "src/spdlog.cpp"
    }

    includedirs
    {
        "include"
    }

    defines
    {
        "SPDLOG_COMPILED_LIB",
    }

    filter "system:linux"
		pic "On"
    
    filter "configurations:Debug"
        runtime "Debug"
        symbols "on"

    filter "configurations:Release"
        runtime "Release"
        optimize "on"
