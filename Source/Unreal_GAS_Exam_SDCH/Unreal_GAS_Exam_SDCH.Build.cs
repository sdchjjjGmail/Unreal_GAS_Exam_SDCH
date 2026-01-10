// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class Unreal_GAS_Exam_SDCH : ModuleRules
{
	public Unreal_GAS_Exam_SDCH(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

		PublicDependencyModuleNames.AddRange(new string[] { "Core", "CoreUObject", "Engine", "InputCore", "EnhancedInput", "Niagara" });

        PrivateDependencyModuleNames.AddRange(new string[] {
            "GameplayAbilities", "GameplayTags", "GameplayTasks",
            "UMG"
        });
    }
}
