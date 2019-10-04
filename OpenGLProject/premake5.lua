project "OpenGLProject"
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
        "%{wks.location}/commons",
        "%{IncludeDir.glm}/glm/**.hpp",
        "%{IncludeDir.glm}/glm/**.inl",
        "%{IncludeDir.stb}/*.h",
        "%{IncludeDir.stb}/*.cpp",
    }

    includedirs
    {
        "src",
        "%{wks.location}/commons",
        "%{IncludeDir.GLFW}",
        "%{IncludeDir.GLEW}",
        "%{IncludeDir.spdlog}",
        "%{IncludeDir.fmt}",
        "%{IncludeDir.glm}",
        "%{IncludeDir.bullet}",
        "%{IncludeDir.stb}",
        "%{IncludeDir.freetype}",
    }

    libdirs
    {
        "%{LibDir.freetype}",
    }

    links 
    { 
        "GLFW",
        "GLEW",
        "fmt",
        "spdlog",
        "bullet",
        "freetype",
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
            "GL",
            "X11", --https://stackoverflow.com/a/17772217
            "Xxf86vm",
            "Xrandr",
            "pthread",
            "Xi", --
            "dl", -- http://discourse.glfw.org/t/how-to-prevent-glfw-from-trying-to-link-vulkan-functions/839
        }

    filter "configurations:Debug"
        defines { "DEBUG" }
        symbols "On"

    filter "configurations:Release"
        defines { "RELEASE" }
        optimize "On"