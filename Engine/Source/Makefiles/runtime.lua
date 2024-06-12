--------------------------------------------------------------
-- Runtime
--------------------------------------------------------------
Module.Create("Runtime", function()
	files {
		path.join(RuntimeSourcePath, "Public/**.*"),
		path.join(RuntimeSourcePath, "Private/**.*"),
	}

	vpaths {
		["Public/*"] = {
			path.join(RuntimeSourcePath, "Public/**.*"),
		},
		["Private/*"] = {
			path.join(RuntimeSourcePath, "Private/**.*"),
		}
	}

	includedirs {
		path.join(RuntimeSourcePath, "Public")
	}

	dependson {
		"RHID3D12", "RHIVulkan", "ShaderCompiler", "GUI", "Scene"
	}

	links {
		"Core"
	}
end)