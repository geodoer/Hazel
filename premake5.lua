include "./vendor/premake/premake_customization/solution_items.lua"
include "Dependencies.lua" --将依赖项相关内容封装到一个lua文件当中

workspace "Hazel"
	architecture "x86_64"
	startproject "Hazelnut"

	configurations
	{
		"Debug",
		"Release",
		"Dist"		-- 更快的调试版本
	}

	solution_items
	{
		".editorconfig"
	}

	flags
	{
		"MultiProcessorCompile"
	}

outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"

-- 依赖项
group "Dependencies"
	include "vendor/premake"
	include "Hazel/vendor/Box2D"
	include "Hazel/vendor/GLFW"	--会将"Hazel/vendor/GLFW/premake5.lua"引进来
	include "Hazel/vendor/Glad"
	include "Hazel/vendor/imgui"
	include "Hazel/vendor/yaml-cpp"
group ""

group "Core"
	include "Hazel"
	include "Hazel-ScriptCore"
group ""

group "Tools"
	include "Hazelnut"
group ""

group "Misc"
	include "Sandbox"
group ""
