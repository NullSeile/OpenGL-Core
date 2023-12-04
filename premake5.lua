project "OpenGL-Core"
	kind "StaticLib"
	language "C++"
	cppdialect "C++20"
	staticruntime "on"

	targetdir ("../bin/" .. outputdir .. "/%{prj.name}")
	objdir ("../bin-int/" .. outputdir .. "/%{prj.name}")

	-- pchheader "glpch.h"
	-- pchsource "src/glpch.cpp"

	files {
		"src/**.h",
		"src/**.cpp",
		"vendor/stb/**.h",
		"vendor/glm/glm/**.hpp",
		"vendor/glm/glm/**.inl",
		"vendor/implot/*.h",
		"vendor/implot/*.cpp",
	}

	defines {
		"_CRT_SECURE_NO_WARNINGS"
	}

	IncludeDir = {}
	IncludeDir["GLFW"] = "vendor/GLFW/include"
	IncludeDir["Glad"] = "vendor/Glad/include"
	IncludeDir["ImGui"] = "vendor/imgui"
	IncludeDir["glm"] = "vendor/glm"
	IncludeDir["stb"] = "vendor/stb"
	IncludeDir["ImPlot"] = "vendor/implot"

	includedirs {
		"src",
		"vendor/spdlog/include",
		"%{IncludeDir.GLFW}",
		"%{IncludeDir.Glad}",
		"%{IncludeDir.ImGui}",
		"%{IncludeDir.glm}",
		"%{IncludeDir.stb}",
		"%{IncludeDir.ImPlot}"
	}

	links { 
		"GLFW",
		"Glad",
		"ImGui",
		"opengl32.lib"
	}

	filter "system:windows"
		systemversion "latest"

		defines {
			"GLCORE_PLATFORM_WINDOWS",
			"GLFW_INCLUDE_NONE"
		}

	filter "configurations:Debug"
		defines "GLCORE_DEBUG"
		runtime "Debug"
		symbols "on"

	filter "configurations:Release"
		defines "GLCORE_RELEASE"
		runtime "Release"
		optimize "on"