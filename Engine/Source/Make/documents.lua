project("Documents")
	kind("Utility")
	location(path.join(RootPath, "Build/Utility"))

	files {
		path.join(RootPath, "Engine/Documents/**.md")
	}

	vpaths {
		["Graphics/*"] = { 
			path.join(RootPath, "Engine/Documents/Graphics/**.*"),
		}
	}