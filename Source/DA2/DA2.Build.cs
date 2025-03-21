// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class DA2 : ModuleRules
{
	public DA2(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

		PublicDependencyModuleNames.AddRange(new string[] { "Core", "CoreUObject", "Engine", "InputCore", "EnhancedInput" });
		PublicDependencyModuleNames.AddRange(new[] {
			"FlecsLibrary",
			"UnrealFlecs"
		});
	}
}
