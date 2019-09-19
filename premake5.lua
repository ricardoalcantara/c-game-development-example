workspace "CPPGameDevelopmentExample"
    architecture "x64"
    configurations { "Debug", "Release" }
    startproject "SFMLProject"

outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"

IncludeDir = {}
IncludeDir["GLFW"] = "%{wks.location}/libs/glfw-3.3/include"
IncludeDir["GLEW"] = "%{wks.location}/libs/glew-2.1.0/include"
IncludeDir["spdlog"] = "%{wks.location}/libs/spdlog-1.x/include"
IncludeDir["fmt"] = "%{wks.location}/libs/fmt-6.0.0/include"
IncludeDir["bullet"] = "%{wks.location}/libs/bullet3-2.88/src"
IncludeDir["glm"] = "%{wks.location}/libs/glm"
IncludeDir["stb"] = "%{wks.location}/libs/stb-master"


group "Dependencies"
    include "libs/glew-2.1.0"
    include "libs/glfw-3.3"
    include "libs/spdlog-1.x"
    include "libs/fmt-6.0.0"
    include "ConsoleApp"
    include "SFMLProject"
    include "OpenGLProject"
    include "libs/bullet3-2.88"
    

