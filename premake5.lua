workspace "Shadow"
    architecture "x64"
    configurations
    {
        "Debug",
        "Release",
        "Final"
    }

outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"

project "Shadow"
    location "Shadow"
    kind "SharedLib"
    language "C++"
    buildoptions { "/utf-8" }

    targetdir ("bin/" .. outputdir .. "/%{prj.name}")
    objdir ("temp/" .. outputdir .. "/%{prj.name}")

    files
    {
        "%{prj.name}/src/**.h",
        "%{prj.name}/src/**.cpp"
    }

    includedirs
    {
        "%{prj.name}/vendor/spdlog/include"
    }

    filter "system:windows"
        cppdialect "C++20"
        staticruntime "On"
        systemversion "latest"

        defines
        {
            "SHADOW_PLATFORM_WINDOWS",
            "SHADOW_BUILD_DLL"
        }

        postbuildcommands
        {
            ("{COPY} %{cfg.buildtarget.relpath} ../bin/" .. outputdir .. "/TheGame")
        }

    filter "configurations:Debug"
        defines "SHADOW_DEBUG"
        symbols "On"

    filter "configurations:Release"
        defines "SHADOW_RELEASE"
        optimize "On"

    filter "configurations:Final"
        defines "SHADOW_FINAL"
        optimize "On"

project "TheGame"
    location "TheGame"
    kind "ConsoleApp"
    language "C++"
    buildoptions { "/utf-8" }

    targetdir ("bin/" .. outputdir .. "/%{prj.name}")
    objdir ("temp/" .. outputdir .. "/%{prj.name}")

    files
    {
        "%{prj.name}/src/**.h",
        "%{prj.name}/src/**.cpp"
    }

    includedirs
    {
        "Shadow/vendor/spdlog/include",
        "Shadow/src"
    }

    links
    {
        "Shadow"
    }

    filter "system:windows"
        cppdialect "C++20"
        staticruntime "On"
        systemversion "latest"

        defines
        {
            "SHADOW_PLATFORM_WINDOWS"
        }

    filter "configurations:Debug"
        defines "SHADOW_DEBUG"
        symbols "On"

    filter "configurations:Release"
        defines "SHADOW_RELEASE"
        optimize "On"

    filter "configurations:Final"
        defines "SHADOW_FINAL"
        optimize "On"