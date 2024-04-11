--------------------------------------------------------------
-- Samples
--------------------------------------------------------------
local function MakeSample(projectPath)
	projectName = path.getbasename(projectPath)
	project(projectName)
		kind("ConsoleApp")

		dependson {
			"RHID3D12", "RHIVulkan"
		}

		Project.CppLanguage()
		Project.Location(path.join(BuildOutputPath, "Engine"))
		
		files {
			path.join(projectPath, "**.*")
		}
		
		includedirs {
			path.join(RuntimeSourcePath, "Public"),
			ThirdPartySourcePath
		}

		links {
			"Core"
		}
end

local sampleProjectFolders = os.matchdirs(path.join(SampleSourcePath, "*"))
for _, sampleProject in pairs(sampleProjectFolders) do
	local sampleFiles = os.matchfiles(path.join(sampleProject, "*.*"))
	if sampleFiles and #sampleFiles > 0 then
		MakeSample(sampleProject)
	end
end