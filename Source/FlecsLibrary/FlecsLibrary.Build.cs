﻿using UnrealBuildTool;

public class FlecsLibrary : ModuleRules
{
    public FlecsLibrary(ReadOnlyTargetRules Target) : base(Target)
    {
        PCHUsage = ModuleRules.PCHUsageMode.UseExplicitOrSharedPCHs;

        PublicDependencyModuleNames.AddRange(
            new string[]
            {
                "Core",
            }
        );

        PrivateDependencyModuleNames.AddRange(
            new string[]
            {
                "CoreUObject",
                "Engine",
                "Slate",
                "SlateCore"
            }
        );
        
        PublicIncludePaths.AddRange(new string[] { ModuleDirectory + "/Public" });
        PrivateIncludePaths.AddRange(new string[] { ModuleDirectory + "/Private" });

        if (Target.LinkType == TargetLinkType.Monolithic)
        {
            PublicDefinitions.Add("flecs_STATIC");
        }
        else
        {
            PrivateDefinitions.Add("flecs_EXPORTS");
        }

        PublicDefinitions.Add("FLECS_CPP_NO_AUTO_REGISTRATION = 1");
        //PublicDefinitions.Add("FLECS_NO_OS_API_IMPL = 1");

        if (Target.Configuration < UnrealTargetConfiguration.Test)
        {
            PublicDefinitions.Add("FLECS_SOFT_ASSERT = 1");
        }

        if (Target.Configuration < UnrealTargetConfiguration.Development)
        {
            // A cheesy way to turn off NDEBUG for Flecs
            PublicDefinitions.Add("DUMMYDEFINE\n#ifdef NDEBUG\n#undef NDEBUG\n#endif");
            PublicDefinitions.Add("FLECS_DEBUG = 1");
            PublicDefinitions.Add("FLECS_SANITIZE = 1");
        }
    }
}