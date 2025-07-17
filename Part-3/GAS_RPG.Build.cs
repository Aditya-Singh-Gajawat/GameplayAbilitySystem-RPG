// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class GAS_RPG : ModuleRules
{
	public GAS_RPG(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

		PublicDependencyModuleNames.AddRange(new string[] 
		{ 
			"Core", 
			"CoreUObject", 
			"Engine", 
			"InputCore", 
			"EnhancedInput", 
			"GameplayTags",
            "EnhancedInput",
			"GameplayTasks",
			"AnimGraphRuntime",
            "MotionWarping"
        });
	}
}
