--------------------------------------------------------------
-- Runtime
--------------------------------------------------------------
project("Engine")
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
		path.join(RootPath, "Engine/Source/Runtime/**.*")
	}