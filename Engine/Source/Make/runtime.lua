--------------------------------------------------------------
-- Runtime
--------------------------------------------------------------
group("Runtime")

Module.Create("Core", function()
	files {
		path.join(RootPath, "Engine/Source/Runtime/Public/Core/**.*"),
		path.join(RootPath, "Engine/Source/Runtime/Private/Core/**.*"),
		path.join(RootPath, "Engine/Source/Runtime/Public/RHI/**.*"),
	}

	vpaths {
		["Public/*"] = {
			path.join(RootPath, "Engine/Source/Runtime/Public/Core/**.*"),
		},
		["Public/RHI/*"] = {
			path.join(RootPath, "Engine/Source/Runtime/Public/RHI/**.*"),
		},
		["Private/*"] = {
			path.join(RootPath, "Engine/Source/Runtime/Private/Core/**.*"),
		}
	}

	Project.LinkD3D12()
end)

Module.Create("RHID3D12", function()
	files {
		path.join(RootPath, "Engine/Source/Runtime/Private/RHI/D3D12/**.*"),
	}

	vpaths {
		["*"] = path.join(RootPath, "Engine/Source/Runtime/Private/RHI/D3D12/**.*"),
	}

	links {
		"Core"
	}

	Project.LinkD3D12()
end)

Module.Create("RHIVulkan", function()
	files {
		path.join(RootPath, "Engine/Source/Runtime/Private/RHI/Vulkan/**.*"),
	}

	vpaths {
		["*"] = path.join(RootPath, "Engine/Source/Runtime/Private/RHI/Vulkan/**.*"),
	}

	links {
		"Core"
	}

	Project.LinkVulkan()
end)

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

group("")