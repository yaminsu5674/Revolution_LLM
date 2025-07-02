// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class Revolution_LLM : ModuleRules
{
	public Revolution_LLM(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

		PublicDependencyModuleNames.AddRange(new string[] { "Core", "CoreUObject", "Engine", "InputCore", "EnhancedInput", "UMG" });
	}
}
