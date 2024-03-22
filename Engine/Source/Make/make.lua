project("Make")
	kind("Utility")
	location(path.join(RootPath, "Build/Utility"))
	files {
		path.join(RootPath, "Engine/Source/Make/**.lua")
	}

	filter { "system:windows", "action:vs2022" }
		prebuildcommands {
			"cd "..RootPath,
			"make_win64_vs2022.bat",
		}
	filter {}