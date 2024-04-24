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
		path.join(ThirdPartySourcePath, "D3D12MemoryAllocator/D3D12MemAlloc.h"),
		path.join(ThirdPartySourcePath, "D3D12MemoryAllocator/D3D12MemAlloc.cpp"),
	}

	vpaths {
		["*"] = path.join(RootPath, "Engine/Source/Runtime/Private/RHI/D3D12/**.*"),
	}

	links {
		"Core",
		"d3d12.lib", "dxgi.lib", "d3dcompiler.lib"
	}
end)

Module.Create("RHIVulkan", function()
	files {
		path.join(RootPath, "Engine/Source/Runtime/Private/RHI/Vulkan/**.*"),
		path.join(ThirdPartySourcePath, "volk/volk.h"),
		path.join(ThirdPartySourcePath, "VulkanMemoryAllocator/vk_mem_alloc.h"),
	}

	vpaths {
		["*"] = path.join(RootPath, "Engine/Source/Runtime/Private/RHI/Vulkan/**.*"),
	}

	links {
		"Core"
	}

	local vulkanSDKPath = os.getenv("VULKAN_SDK")
	if vulkanSDKPath == nil then
		Log.Warning("Environment variable VULKAN_SDK not defined.")
	else
		Log.Info("Find VULKAN_SDK : "..vulkanSDKPath)

		links { "$(VULKAN_SDK)/lib/vulkan-1.lib" }
		includedirs { "$(VULKAN_SDK)/include" }
	end
end)

group("")