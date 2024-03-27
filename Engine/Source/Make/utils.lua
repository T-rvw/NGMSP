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

Project.LinkVulkan = function()
	local vulkanSDKPath = os.getenv("VULKAN_SDK")
	if vulkanSDKPath == nil then
		Log.Warning("Environment variable VULKAN_SDK not defined.")
		return
	end

	Log.Info("Find VULKAN_SDK : "..vulkanSDKPath)
    links { "$(VULKAN_SDK)/lib/vulkan-1.lib" }
    includedirs { "$(VULKAN_SDK)/include" }
end