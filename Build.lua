workspace "SEngine"
	architecture "x64"
	startproject "Sandbox"

	configurations
	{
		"Debug",
		"Release",
		"Dist"
	}

	flags
	{
		"MultiProcessorCompile"
	}

outputdir = "%{cfg.system}-%{cfg.architecture}/%{cfg.buildcfg}"

include "SEngine/Build-SEngine.lua"

include "Sandbox/Build-Sandbox.lua"