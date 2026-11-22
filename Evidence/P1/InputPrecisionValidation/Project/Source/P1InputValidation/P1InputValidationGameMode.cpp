#include "P1InputValidationGameMode.h"
#include "P1InputValidationController.h"
#include "InputPrecisionSampler.h"
#include "Engine/World.h"
#include "GameInputDeveloperSettings.h"

namespace
{
void ConfigureDualSenseGameInput()
{
    UGameInputDeveloperSettings* Settings = GetMutableDefault<UGameInputDeveloperSettings>();
    const FGameInputDeviceConfiguration* Found = Settings->FindDeviceConfiguration(FGameInputDeviceIdentifier(0x054c, 0x0df2));
    if (!Found)
    {
        UE_LOG(LogTemp, Warning, TEXT("P1_INPUT DualSense GameInput configuration not found"));
        return;
    }

    FGameInputDeviceConfiguration* Config = const_cast<FGameInputDeviceConfiguration*>(Found);
    Config->ControllerAxisMappingData.Reset();
    Config->ControllerButtonMappingData.Reset();

    auto AddAxis = [Config](uint32 Index, const TCHAR* KeyName, float DeadZone, float Scalar, bool Packed)
    {
        FGameInputControllerAxisData Data;
        Data.KeyName = FName(KeyName);
        Data.DeadZone = DeadZone;
        Data.Scalar = Scalar;
        Data.bIsPackedPositveAndNegative = Packed;
        Config->ControllerAxisMappingData.Add(Index, Data);
    };

    AddAxis(0, TEXT("Gamepad_LeftX"), 0.0f, 1.0f, true);
    AddAxis(1, TEXT("Gamepad_LeftY"), 0.0f, -1.0f, true);
    AddAxis(2, TEXT("Gamepad_RightX"), 0.0f, 1.0f, true);
    AddAxis(3, TEXT("Gamepad_LeftTriggerAxis"), 0.0f, 1.0f, false);
    AddAxis(4, TEXT("Gamepad_RightTriggerAxis"), 0.0f, 1.0f, false);
    AddAxis(5, TEXT("Gamepad_RightY"), 0.0f, 1.0f, true);

    const TPair<uint32, FName> Buttons[] =
    {
        {1u << 0, FName(TEXT("Gamepad_FaceButton_Left"))},
        {1u << 1, FName(TEXT("Gamepad_FaceButton_Bottom"))},
        {1u << 2, FName(TEXT("Gamepad_FaceButton_Right"))},
        {1u << 3, FName(TEXT("Gamepad_FaceButton_Top"))},
        {1u << 4, FName(TEXT("Gamepad_LeftShoulder"))},
        {1u << 5, FName(TEXT("Gamepad_RightShoulder"))},
        {1u << 6, FName(TEXT("Gamepad_LeftTrigger"))},
        {1u << 7, FName(TEXT("Gamepad_RightTrigger"))},
        {1u << 8, FName(TEXT("Gamepad_Special_Left"))},
        {1u << 9, FName(TEXT("Gamepad_Special_Right"))},
        {1u << 10, FName(TEXT("Gamepad_LeftThumbstick"))},
        {1u << 11, FName(TEXT("Gamepad_RightThumbstick"))}
    };
    for (const TPair<uint32, FName>& Button : Buttons)
    {
        Config->ControllerButtonMappingData.Add(Button);
    }
    UE_LOG(LogTemp, Display, TEXT("P1_INPUT DualSense GameInput mappings initialized: %d axes, %d buttons"), Config->ControllerAxisMappingData.Num(), Config->ControllerButtonMappingData.Num());
}
}

AP1InputValidationGameMode::AP1InputValidationGameMode()
{
    PlayerControllerClass = AP1InputValidationController::StaticClass();
    DefaultPawnClass = nullptr;
}
void AP1InputValidationGameMode::BeginPlay()
{
    Super::BeginPlay();
    ConfigureDualSenseGameInput();
    if (GetWorld())
    {
        GetWorld()->SpawnActor<AP1InputPrecisionSampler>(FVector::ZeroVector, FRotator::ZeroRotator);
    }
}

