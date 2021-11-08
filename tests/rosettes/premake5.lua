
project "rosettes"
	location "./"
	--possible values: ConsoleApp, SharedLib, StaticLib, Makefile, Utility, Packaging
	kind "ConsoleApp"
	outputdir = "%{cfg.buildcfg}"

	language "C++"
	cppdialect "C++17"
	--buildoptions { "-pthread" }

	targetdir ("bin/" .. outputdir)
	objdir ("build/" .. outputdir)


	files
	{
		"src/**.h",
		"src/**.cpp",
	}

	includedirs
	{
		"%{wks.location}/StarLib/src",
		"%{wks.location}/StarLib/src/**",
		"%{wks.location}/StarLib/vendor/entt",
	}

	links {"StarLib", "gtest"}

	filter "configurations:Debug"
		symbols "On"
		defines "DEBUG"

	filter "configurations:Release"
		-- defines...
		optimize "On"
		defines "RELEASE"

	filter "configurations:Dist"
		-- defines...
		optimize "On"
