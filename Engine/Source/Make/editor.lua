--------------------------------------------------------------
-- Editor
--------------------------------------------------------------
project("Editor")
	kind("ConsoleApp")

	Project.CppLanguage()
	Project.Location(path.join(BuildOutputPath, "Editor"))

	defines {
	}
	
	includedirs {
	}

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
	
	flags {
		"MultiProcessorCompile", -- speed up compile
		"FatalWarnings", -- treat warnings as errors
	}
	
	files {
		path.join(RootPath, "Engine/Source/Editor/**.*")
	}