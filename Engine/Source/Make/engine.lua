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

	-- TODO : Use /MD[d] because we are using STL as dll class's APIs currently.
	-- Dll contains its own copy of the C Runtime and heap manager in /MT[d]. 
	staticruntime "off"
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
	
	files {
		path.join(RootPath, "Engine/Source/Runtime/**.*"),
		path.join(ThirdPartySourcePath, "nameof/nameof.hpp"),
	}

	vpaths {
		["Public/*"] = path.join(RootPath, "Engine/Source/Runtime/Public/**.*"),
		["Private/*"] = path.join(RootPath, "Engine/Source/Runtime/Private/**.*"),
		["ThirdParty/*"] = path.join(ThirdPartySourcePath, "**.*"),
	}

	Project.LinkD3D12()
	Project.LinkVulkan()