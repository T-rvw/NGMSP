--------------------------------------------------------------
-- Dump
--------------------------------------------------------------
Dump = {}
Dump.PrintVar = function(name, value)
	term.pushColor(term.cyan)
	print(name.." : "..value)
	term.popColor()
end

--------------------------------------------------------------
-- Log
--------------------------------------------------------------
Log = {}
Log.Info = function(msg)
	term.pushColor(term.green)
	print("[Info] "..msg)
	term.popColor()
end

Log.Warning = function(msg)
	term.pushColor(term.yellow)
	print("[Warning] "..msg)
	term.popColor()
end

Log.Error = function(msg)
	term.pushColor(term.red)
	print("[Error] "..msg)
	term.popColor()
end

--------------------------------------------------------------
-- Project
--------------------------------------------------------------
Project = {}
Project.CppLanguage = function()
	language("C++")
	cppdialect("c++20")
end

Project.Location = function(outputPath)
	location(outputPath)
	objdir("%{prj.location}/Intermediate/%{cfg.buildcfg}_%{cfg.architecture}")
	targetdir("%{prj.location}/Binaries/%{cfg.buildcfg}_%{cfg.architecture}")
end

Project.StaticRuntime = function(flag)
	-- Dll contains its own copy of the C Runtime and heap manager in /MT[d]. 
	staticruntime(flag)
	filter { "configurations:Debug" }
		runtime("Debug")
	filter { "configurations:Release" }
		runtime("Release")
	filter {}
end

--------------------------------------------------------------
-- Module
--------------------------------------------------------------
Module = {}
Module.Create = function(moduleName, moduleCallback)
	project(moduleName)
		kind("SharedLib")

		Project.CppLanguage()
		Project.Location(path.join(BuildOutputPath, "Engine"))
		Project.StaticRuntime("on")

		defines {
			"ENGINE_BUILD_SHARED",
			"PLATFORM_WINDOWS"
		}
	
		includedirs {
			path.join(RuntimeSourcePath, "Public"),
			ThirdPartySourcePath
		}

		-- Disable these options can reduce the size of compiled binaries.
		justmycode("Off")
		editAndContinue("Off")
		exceptionhandling("Off")
		rtti("Off")	
	
		-- Strict compile.
		warnings("Default")
		externalwarnings("Off")
	
		flags {
			"MultiProcessorCompile", -- speed up compile
			"FatalWarnings", -- treat warnings as errors
		}

		vpaths {
			["ThirdParty/*"] = path.join(ThirdPartySourcePath, "**.*"),
		}

		if moduleCallback then
			moduleCallback()
		end
end