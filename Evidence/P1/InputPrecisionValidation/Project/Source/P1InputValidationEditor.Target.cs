using UnrealBuildTool;
public class P1InputValidationEditorTarget : TargetRules
{
    public P1InputValidationEditorTarget(TargetInfo Target) : base(Target)
    {
        Type = TargetType.Editor;
        DefaultBuildSettings = BuildSettingsVersion.V8;
        IncludeOrderVersion = EngineIncludeOrderVersion.Unreal5_9;
        ExtraModuleNames.Add("P1InputValidation");
    }
}
