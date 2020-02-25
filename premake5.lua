workspace "EngineDesignPatterns"

    -- System architecture (64 bit)
    architecture "x64"
    startproject "EngineDesignPatterns"

    configurations
    {
        "Debug",
        "Release",
    }

-- Output directories
outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"

-- C/C++ include directories relative to root folder (=solution directory)
IncludeDir = {}
IncludeDir["GLM"] =     "EngineDesignPatterns/external/GLM"
IncludeDir["GLFW"] =    "EngineDesignPatterns/external/GLFW/include"
IncludeDir["GLAD"] =    "EngineDesignPatterns/external/GLAD/include"

-----------------------------------------------------------------------------------------------------------

project "EngineDesignPatterns"
    location "EngineDesignPatterns"
    kind "ConsoleApp"
    language "C++"
    cppdialect "C++17"
    staticruntime "on"
    
    targetdir ("bin/" .. outputdir .. "/%{prj.name}")
    objdir ("build/" .. outputdir .. "/%{prj.name}")

    -- Sets which files should be included in the project
    files
    {
        "%{prj.name}/src/**.h",
        "%{prj.name}/src/**.cpp",
        "%{prj.name}/external/GLAD/src/glad.c"
    }

    -- Sets additional include directories (adds files to a project)
    includedirs
    {
        "%{prj.name}/src",      -- included so that headers can be included from the source
        "%{IncludeDir.GLM}",
        "%{IncludeDir.GLFW}",
        "%{IncludeDir.GLAD}",
    }
    
    -- Sets additional dependencies (.lib files)
    links 
    { 
        "opengl32.lib",	
        "glfw3.lib", 
        "glfw3dll.lib",
    }

    -- Sets library paths
    libdirs { 
        "%{prj.name}/external/GLFW/lib",
    }

    -- Build configurations (runtime sets runtime library to /MDd for Debug and /MD to all other configs)
    filter "configurations:Debug"
        defines "Debug"
        runtime "Debug"
        symbols "on"

    filter "configurations:Release"
        defines "Release"
        runtime "Release"
        optimize "on"