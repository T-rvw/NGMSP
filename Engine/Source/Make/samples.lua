--------------------------------------------------------------
-- Samples
--------------------------------------------------------------
local function MakeSample(projectPath)
	projectName = path.getbasename(projectPath)
	project(projectName)
		kind("ConsoleApp")

		Project.CppLanguage()
		Project.Location(path.join(BuildOutputPath, "Engine"))
		
		defines {
			"PLATFORM_WINDOWS"
		}
		
		files {
			path.join(projectPath, "**.*")
		}
		
		includedirs {
			path.join(RuntimeSourcePath, "Public"),
			ThirdPartySourcePath
		}

		links {
			"Engine"
		}
end

local sampleProjectFolders = os.matchdirs(path.join(SampleSourcePath, "*"))
for _, sampleProject in pairs(sampleProjectFolders) do
	Log.Info(sampleProject)
	local sampleFiles = os.matchfiles(path.join(sampleProject, "*.*"))
	if sampleFiles and #sampleFiles > 0 then
		MakeSample(sampleProject)
	end
end