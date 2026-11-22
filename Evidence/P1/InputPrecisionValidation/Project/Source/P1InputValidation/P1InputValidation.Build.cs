using UnrealBuildTool;
public class P1InputValidation : ModuleRules
{
    public P1InputValidation(ReadOnlyTargetRules Target) : base(Target)
    {
        PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;
        PublicDependencyModuleNames.AddRange(new string[] { "Core", "CoreUObject", "Engine", "EnhancedInput", "InputCore", "RawInput" });
    }
}



