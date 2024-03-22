--------------------------------------------------------------
-- Dump
--------------------------------------------------------------
function DumpVariable(name, value)
	print(name.." : "..value)
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