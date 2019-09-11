workspace "CPPGameDevelopmentExample"
    architecture "x64"
    configurations { "Debug", "Release" }
    startproject "SFMLProject"

outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"

IncludeDir = {}
IncludeDir["GLFW"] = "%{wks.location}/libs/glfw-3.3/include"
IncludeDir["GLEW"] = "%{wks.location}/libs/glew-2.1.0/include"
IncludeDir["glm"] = "%{wks.location}/libs/glm"
IncludeDir["spdlog"] = "%{wks.location}/libs/spdlog-1.x/include"
IncludeDir["fmt"] = "%{wks.location}/libs/fmt-6.0.0/include"

group "Dependencies"
    include "libs/glew-2.1.0"
    include "libs/glfw-3.3"
    include "libs/spdlog-1.x"
    include "libs/fmt-6.0.0"
    include "ConsoleApp"
    include "SFMLProject"
    include "OpenGLProject"
    

