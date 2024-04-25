--------------------------------------------------------------
-- Samples
--------------------------------------------------------------
local SampleFrameworkName = "SampleCommon"
project(SampleFrameworkName)
	kind("StaticLib")

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

	files {
		path.join(SampleSourcePath, "SampleCommon/**.*")
	}

	-- Disable these options can reduce the size of compiled binaries.
	justmycode("Off")
	editAndContinue("Off")
	exceptionhandling("Off")
	rtti("Off")	
	
	flags {
		"MultiProcessorCompile", -- speed up compile
	}

	links {
		"Core", "Graphics"
	}

local function MakeSample(projectPath)
	projectName = path.getbasename(projectPath)
	project(projectName)
		kind("ConsoleApp")

		Project.CppLanguage()
		Project.Location(path.join(BuildOutputPath, "Engine"))
		Project.StaticRuntime("on")

		files {
			path.join(projectPath, "**.*")
		}
		
		includedirs {
			path.join(RuntimeSourcePath, "Public"),
			path.join(SampleSourcePath, SampleFrameworkName),
			ThirdPartySourcePath
		}

		dependson {
			SampleFrameworkName
		}

		links {
			"Core", SampleFrameworkName
		}
end

local sampleProjectFolders = os.matchdirs(path.join(SampleSourcePath, "*"))
for _, sampleProject in pairs(sampleProjectFolders) do
	sampleName = path.getbasename(sampleProject)
	if sampleName ~= SampleFrameworkName then
		local sampleFiles = os.matchfiles(path.join(sampleProject, "*.*"))
		if sampleFiles and #sampleFiles > 0 then
			MakeSample(sampleProject)
		end
	end
end