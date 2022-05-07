// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class KillaSoft_TEST : ModuleRules
{
	public KillaSoft_TEST(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

		PublicDependencyModuleNames.AddRange(new string[] { "Core", "CoreUObject", "Engine", "InputCore", "HeadMountedDisplay" });
	}
}
