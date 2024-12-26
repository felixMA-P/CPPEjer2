// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class Ejercicio2CPP : ModuleRules
{
	public Ejercicio2CPP(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

		PublicDependencyModuleNames.AddRange(new string[] { "Core", "CoreUObject", "Engine", "InputCore", "EnhancedInput" });
	}
}
