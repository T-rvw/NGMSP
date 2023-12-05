--------------------------------------------------------------
-- Makefile
--------------------------------------------------------------
CurrentWorkingPath = os.getcwd()
RootPath = string.sub(CurrentWorkingPath, 0, string.len(CurrentWorkingPath) - string.len("Auto") - 1)
ThirdPartySourcePath = path.join(RootPath, "ThirdParty")

--------------------------------------------------------------
-- Workspace
--------------------------------------------------------------
workspace("NGMSP")
	architecture "x64"
	location(RootPath)
	system("windows")
	systemversion("latest")

	configurations { "Debug", "Release" }
	filter "configurations:Debug"
		defines { "_DEBUG" }
		symbols("On")
		optimize("Off")
	filter "configurations:Release"
		defines { "NDEBUG" }
		symbols("On")
		optimize("Full")
	filter {}
	

--------------------------------------------------------------	
-- Utility Project
--------------------------------------------------------------
group("Build")
project("AutoMake")
	kind("Utility")
	location(path.join(RootPath, "Build"))
	files
	{
		path.join(RootPath, "Auto/**.lua")
	}

	filter { "system:windows", "action:vs2022" }
		prebuildcommands
		{
			"cd "..RootPath,
			"make_win64_vs2022.bat",
		}
	filter {}
group("")

--------------------------------------------------------------
-- Demo
--------------------------------------------------------------
project("Demo")
	kind("ConsoleApp")
	language("C++")
	cppdialect("c++latest")

	location(path.join(RootPath, "Build"))
	objdir("%{prj.location}/obj/%{cfg.buildcfg}")
	targetdir("%{prj.location}/bin/%{cfg.buildcfg}")

	-- use /MT /MTd, not /MD /MDd
	staticruntime "on"
	filter { "configurations:Debug" }
		runtime "Debug" -- /MTd
	filter { "configurations:Release" }
		runtime "Release" -- /MT
	filter {}
	
	-- Disable these options can reduce the size of compiled binaries.
	justmycode("Off")
	editAndContinue("Off")
	exceptionhandling("Off")
	rtti("Off")	
	
	-- Strict compile.
	warnings("Default")
	externalwarnings("Off")
	
	flags
	{
		"MultiProcessorCompile", -- speed up compile
		"FatalWarnings", -- treat warnings as errors
	}
	
	files { path.join(RootPath, "Source/**.*") }