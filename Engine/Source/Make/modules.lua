--------------------------------------------------------------
-- Modules
--------------------------------------------------------------
group("Modules")

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

group("")