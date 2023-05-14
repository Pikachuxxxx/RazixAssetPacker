-- Razix Engine vendor Common Inlcudes 
include 'Scripts/premake/common/vendor_includes.lua'
-- Internal libraies include dirs
include 'Scripts/premake/common/internal_includes.lua'

project "RazixAssetPacker"
    kind "StaticLib"
    language "C++"
    cppdialect "C++17"
    staticruntime "off"

    includedirs
    {
         "./",
         "./common",
         "./importer",
         "./exporter",
         "./vendor/assimp/include",
         -- Razix
         "%{IncludeDir.Razix}",
         -- GLM
        "%{IncludeDir.glm}",
        "%{IncludeDir.cereal}"
    }

    files
    {
        "./common/**.h",
        "./common/**.c",
        "./common/**.cpp",
        "./importer/**.h",
        "./importer/**.c",
        "./importer/**.cpp",
        "./exporter/**.h",
        "./exporter/**.c",
        "./exporter/**.cpp"
    }

    removefiles
    {
        "./cli/**"
    }

    links
    {
        "assimp"
    }

    filter "system:windows"
        systemversion "latest"
        cppdialect "C++17"
        staticruntime "off"

    filter "configurations:Debug"
        defines { "RAZIX_DEBUG", "_DEBUG" }
        symbols "On"
        runtime "Debug"
        optimize "Off"

    filter "configurations:Release"
        defines { "RAZIX_RELEASE", "NDEBUG" }
        optimize "Speed"
        symbols "On"
        runtime "Release"

    filter "configurations:Distribution"
        defines { "RAZIX_DISTRIBUTION", "NDEBUG" }
        symbols "Off"
        optimize "Full"
        runtime "Release"
