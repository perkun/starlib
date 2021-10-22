project "StarLib"
	outputdir = "%{cfg.buildcfg}"
	location "./"
	--possible values: ConsoleApp, SharedLib, StaticLib, Makefile, Utility, Packaging
	kind "StaticLib"

	language "C++"
	cppdialect "C++17"
	--buildoptions { "-pthread" }

	targetdir ("bin/" .. outputdir)
	objdir ("build/" .. outputdir)


	files
	{
		"src/**.h",
		"src/**.cpp",
		"src/**.cc",
	}

	includedirs
	{
		"src",
		"src/**",
 		"vendor/entt",
	}

	links {}

	filter "configurations:Debug"
		symbols "On"
		defines "DEBUG"
		defines "MCM_POT_PATH=\"/home/perkun/projects/integrators/StarLib/data/pot\""

	filter "configurations:Release"
		-- defines...
		optimize "On"
		defines "RELEASE"
		defines "MCM_POT_PATH=\"/home/perkun/projects/integrators/StarLib/data/pot\""

	filter "configurations:Dist"
		-- defines...
		optimize "On"
