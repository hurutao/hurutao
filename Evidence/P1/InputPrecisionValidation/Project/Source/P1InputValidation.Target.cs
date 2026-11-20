using UnrealBuildTool;
public class P1InputValidationTarget : TargetRules
{
    public P1InputValidationTarget(TargetInfo Target) : base(Target) { Type = TargetType.Game; ExtraModuleNames.Add("P1InputValidation"); }
}
