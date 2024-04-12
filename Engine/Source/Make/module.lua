--------------------------------------------------------------
-- Module
--------------------------------------------------------------
Module = {}

Module.Create = function(moduleName, moduleCallback)
	project(moduleName)
		kind("SharedLib")

		Project.CppLanguage()
		Project.Location(path.join(BuildOutputPath, "Engine"))

		defines {
			"ENGINE_BUILD_SHARED",
			"PLATFORM_WINDOWS"
		}
	
		includedirs {
			path.join(RuntimeSourcePath, "Public"),
			ThirdPartySourcePath
		}

		-- Dll contains its own copy of the C Runtime and heap manager in /MT[d]. 
		staticruntime "on"
		filter { "configurations:Debug" }
			runtime "Debug"
		filter { "configurations:Release" }
			runtime "Release"
		filter {}
	
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
			--["Public/*"] = path.join(RootPath, "Engine/Source/Runtime/Public/**.*"),
			--["Private/*"] = path.join(RootPath, "Engine/Source/Runtime/Private/**.*"),
			["ThirdParty/*"] = path.join(ThirdPartySourcePath, "**.*"),
		}

		if moduleCallback then
			moduleCallback()
		end
end