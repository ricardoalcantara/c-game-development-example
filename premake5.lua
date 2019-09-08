workspace "CPPGameDevelopmentExample"
    architecture "x64"
    configurations { "Debug", "Release" }
    startproject "SFMLProject"

outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"

IncludeDir = {}
IncludeDir["spdlog"] = "%{wks.location}/libs/spdlog-1.x/include"

group "Dependencies"
    include "libs/spdlog-1.x"
    include "SFMLProject"
    

