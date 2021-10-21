
project "simulation"
	location "./"
	--possible values: ConsoleApp, SharedLib, StaticLib, Makefile, Utility, Packaging
	outputdir = "%{cfg.buildcfg}"
	kind "ConsoleApp"

	language "C++"
	cppdialect "C++17"
	--buildoptions { "-pthread" }

	targetdir ("bin/" .. outputdir)
	objdir ("build/" .. outputdir)


	files
	{
		"src/**.h",
		"src/**.cpp"
	}

	includedirs
	{
	}

	links {}

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