dofile("utils.lua")

--------------------------------------------------------------
-- Path
--------------------------------------------------------------
CurrentWorkingPath = os.getcwd()
RootPath = string.sub(CurrentWorkingPath, 0, string.len(CurrentWorkingPath) - string.len("Engine/Source/Makefiles") - 1)
BuildOutputPath = path.join(RootPath, "Build")
EngineSourcePath = path.join(RootPath, "Engine/Source")
MakefileSourcePath = path.join(RootPath, "Engine/Source/Makefiles")
EditorSourcePath = path.join(RootPath, "Engine/Source/Editor")
PluginSourcePath = path.join(RootPath, "Engine/Source/Plugins")
ModuleSourcePath = path.join(RootPath, "Engine/Source/Modules")
RuntimeSourcePath = path.join(RootPath, "Engine/Source/Runtime")
SampleSourcePath = path.join(RootPath, "Engine/Source/Samples")
ThirdPartyPath = path.join(RootPath, "Engine/ThirdParty")
ThirdPartySourcePath = path.join(RootPath, "Engine/Source/ThirdParty")

--------------------------------------------------------------
-- Dump Info
--------------------------------------------------------------
Log.Info("-----------------------Path---------------------------")
Dump.PrintVar("RootPath", RootPath)
Dump.PrintVar("EngineSourcePath", EngineSourcePath)
Dump.PrintVar("EditorSourcePath", EditorSourcePath)
Dump.PrintVar("PluginSourcePath", PluginSourcePath)
Dump.PrintVar("RuntimeSourcePath", RuntimeSourcePath)
Dump.PrintVar("SampleSourcePath", SampleSourcePath)
Dump.PrintVar("ThirdPartySourcePath", ThirdPartySourcePath)
Log.Info("------------------------------------------------------")

--------------------------------------------------------------
-- Workspace
--------------------------------------------------------------
workspace("NGMSP")
	architecture "x64"
	location(RootPath)
	system("windows")
	systemversion("latest")
	startproject("00_HelloWorld")

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
dofile("make.lua")
group("")

group("Resources")
dofile("documents.lua")
group("")

group("Modules")
dofile("modules.lua")
group("")

group("Runtime")
dofile("runtime.lua")
group("")

group("Samples")
dofile("samples.lua")
group("")