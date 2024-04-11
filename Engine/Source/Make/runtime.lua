--------------------------------------------------------------
-- Runtime
--------------------------------------------------------------
group("Runtime")

Module.Create("Core", function()
	files {
		path.join(RootPath, "Engine/Source/Runtime/Public/Core/**.*"),
		path.join(RootPath, "Engine/Source/Runtime/Private/Core/**.*"),
	}

	Project.LinkD3D12()
end)

Module.Create("RHID3D12", function()
	files {
		path.join(RootPath, "Engine/Source/Runtime/Private/RHI/D3D12/**.*"),
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

	links {
		"Core"
	}

	Project.LinkVulkan()
end)

group("")