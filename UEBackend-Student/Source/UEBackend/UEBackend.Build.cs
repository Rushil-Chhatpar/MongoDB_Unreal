// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class UEBackend : ModuleRules
{
	public UEBackend(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

		PublicDependencyModuleNames.AddRange(new string[] { "Core", "CoreUObject", "Engine", "InputCore", "HeadMountedDisplay", "EnhancedInput", "SocketIOClient", "SocketIOLib", "Json", "SIOJson", "UMG" });

        PublicIncludePaths.AddRange(
                new string[] {
                    "UEBackend/",
                    "UEBackend/SocketIO/",
                    
                   
					// ... add public include paths required here ...
				}
                );
    }
}
