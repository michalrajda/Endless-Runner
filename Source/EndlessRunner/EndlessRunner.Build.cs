// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class EndlessRunner : ModuleRules
{
	public EndlessRunner(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

		PublicDependencyModuleNames.AddRange(new string[] { "Core", "CoreUObject", "Engine", "InputCore", "HeadMountedDisplay", "EnhancedInput" });

		PublicIncludePaths.AddRange(new string[] { "EndlessRunner/Collectibles", "EndlessRunner/Collectibles/Coin", "EndlessRunner/Collectibles/Boost", "EndlessRunner", "EndlessRunner/Animation", "EndlessRunner/Obstacles", "EndlessRunner/Spawners", "EndlessRunner/UI", "EndlessRunner/MainClasses", "EndlessRunner/LevelLoader", "EndlessRunner/Lamps" });

        PrivateDependencyModuleNames.AddRange(new string[] { "Slate", "SlateCore" });
    }
}
