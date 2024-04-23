--------------------------------------------------------------
-- Runtime
--------------------------------------------------------------
Module.Create("Graphics", function()
	files {
		path.join(RootPath, "Engine/Source/Runtime/Public/Graphics/**.*"),
		path.join(RootPath, "Engine/Source/Runtime/Private/Graphics/**.*"),
	}

	vpaths {
		["Public/*"] = {
			path.join(RootPath, "Engine/Source/Runtime/Public/Graphics/**.*"),
		},
		["Private/*"] = {
			path.join(RootPath, "Engine/Source/Runtime/Private/Graphics/**.*"),
		}
	}

	dependson {
		"RHID3D12", "RHIVulkan"
	}

	links {
		"Core"
	}
end)