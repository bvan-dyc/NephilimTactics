// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class NephGlitterTactics : ModuleRules
{
	public NephGlitterTactics(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

        PublicDependencyModuleNames.AddRange(new string[]
        {
	        "Core",
	        "CoreUObject",
	        "UMG",
	        "Engine",
	        "InputCore",
	        "EnhancedInput",
	        "CommonUI",
	        "NiagaraCore",
	        "Niagara",
	        "AIModule",
	        "GameplayAbilities",
	        "GameplayTags",
	        "GameplayTasks",
	        "MoviePlayer", 
	        "AdvancedWidgets",
	        "NavigationSystem", 
	        "AIModule",
        });
        
        PublicDependencyModuleNames.AddRange(new string[]
        {
	        "Flow",
        });
    }
}
