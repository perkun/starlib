workspace "starlib2"
	architecture "x64"

	configurations
	{
		"Debug",
		"Release",
		"Dist"
	}

include "StarLib"
include "star_galpot"
include "tests"
include "passing_star"
