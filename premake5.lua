workspace "LightTags"
	architecture "x64"
	startproject "LightTags"
	
	configurations
	{
		"Debug",
		"Release"
	}
	
outputdir= "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"
		
project "LightTags"
	location "LightTags"
	kind "ConsoleApp"
	language "C++"
	
	targetdir ("%{prj.name}/bin/" .. outputdir)
	objdir ("%{prj.name}/intermediate/" .. outputdir)
	
	files
	{
		"%{prj.name}/src/**.h",
		"%{prj.name}/src/**.cpp"
	}

	
	filter "system:windows"
		cppdialect "C++14"
		staticruntime "On"
		systemversion "latest"
		
	
		
		