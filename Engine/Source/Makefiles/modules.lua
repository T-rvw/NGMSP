--------------------------------------------------------------
-- Modules
--------------------------------------------------------------
group("Modules")

Module.Create("Core", function()
	files {
		path.join(ModuleSourcePath, "Public/**.*"),
		path.join(ModuleSourcePath, "Private/Core/**.*"),
	}

	vpaths {
		["Public/*"] = {
			path.join(ModuleSourcePath, "Public/Core/**.*"),
		},
		["Interfaces/GUI"] = {
			path.join(ModuleSourcePath, "Public/GUI/**.*"),
		},
		["Interfaces/RHI"] = {
			path.join(ModuleSourcePath, "Public/RHI/**.*"),
		},
		["Interfaces/Scene"] = {
			path.join(ModuleSourcePath, "Public/Scene/**.*"),
		},
		["Interfaces/ShaderCompiler"] = {
			path.join(ModuleSourcePath, "Public/ShaderCompiler/**.*"),
		},
		["Private/*"] = {
			path.join(ModuleSourcePath, "Private/**.*"),
		}
	}
end)

Module.Create("RHID3D12", function()
	files {
		path.join(ModuleSourcePath, "Private/RHI/D3D12/**.*"),
		path.join(ThirdPartySourcePath, "D3D12MemoryAllocator/D3D12MemAlloc.h"),
		path.join(ThirdPartySourcePath, "D3D12MemoryAllocator/D3D12MemAlloc.cpp"),
	}

	vpaths {
		["*"] = path.join(ModuleSourcePath, "Private/RHI/D3D12/**.*"),
	}

	links {
		"Core",
		"d3d12", "dxgi", "d3dcompiler",
	}
end)

Module.Create("RHIVulkan", function()
	files {
		path.join(ModuleSourcePath, "Private/RHI/Vulkan/**.*"),
		path.join(ThirdPartySourcePath, "volk/volk.h"),
		path.join(ThirdPartySourcePath, "VulkanMemoryAllocator/vk_mem_alloc.h"),
	}

	vpaths {
		["*"] = path.join(ModuleSourcePath, "Private/RHI/Vulkan/**.*"),
	}

	links {
		"Core"
	}

	local vulkanSDKPath = os.getenv("VULKAN_SDK")
	if vulkanSDKPath == nil then
		Log.Warning("Environment variable VULKAN_SDK not defined.")
	else
		Log.Info("Find VULKAN_SDK : "..vulkanSDKPath)

		links { "$(VULKAN_SDK)/lib/vulkan-1" }
		includedirs { "$(VULKAN_SDK)/include" }
	end
end)

Module.Create("ShaderCompiler", function()
	files {
		path.join(ModuleSourcePath, "Private/ShaderCompiler/**.*"),
	}

	vpaths {
		["*"] = path.join(ModuleSourcePath, "Private/ShaderCompiler/**.*"),
	}

	includedirs {
		path.join(ThirdPartyPath, "dxc/include"),
	}

	libdirs {
		path.join(ThirdPartyPath, "dxc/lib"),
	}

	links {
		"Core",
		"dxcompiler"
	}

	postbuildcommands {
		"{COPYFILE} \""..path.join(ThirdPartyPath, "dxc/bin/*.*").."\" \""..Project.GetBinariesDirectory().."\"",
	}
end)

Module.Create("GUI", function()
	files {
		path.join(ModuleSourcePath, "Private/GUI/**.*"),
	}

	vpaths {
		["*"] = path.join(ModuleSourcePath, "Private/GUI/**.*"),
	}

	links {
		"Core"
	}
end)

Module.Create("Scene", function()
	files {
		path.join(ModuleSourcePath, "Private/Scene/**.*"),
	}

	vpaths {
		["*"] = path.join(ModuleSourcePath, "Private/Scene/**.*"),
	}

	links {
		"Core"
	}
end)

group("")