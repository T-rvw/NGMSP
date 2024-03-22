project("Shaders")
	kind("Utility")
	location(path.join(RootPath, "Build/Utility"))
	files {
		path.join(RootPath, "Engine/Shaders/**.hlsl*")
	}