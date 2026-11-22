#include "P1InputValidationController.h"
#include "EnhancedInputComponent.h"
#include "InputPrecisionSampler.h"
#include "Engine/World.h"
AP1InputValidationController::AP1InputValidationController() {}
void AP1InputValidationController::BeginPlay()
{
    Super::BeginPlay();
    if (GetWorld())
    {
        GetWorld()->SpawnActor<AP1InputPrecisionSampler>(FVector::ZeroVector, FRotator::ZeroRotator);
        UE_LOG(LogTemp, Display, TEXT("P1_INPUT ControllerBeginPlay sampler spawned"));
    }
}
void AP1InputValidationController::SetupInputComponent()
{
    Super::SetupInputComponent();
    if (!Cast<UEnhancedInputComponent>(InputComponent))
    {
        InputComponent = NewObject<UEnhancedInputComponent>(this, TEXT("P1EnhancedInputComponent"));
        InputComponent->RegisterComponent();
        PushInputComponent(InputComponent);
    }
    if (!Cast<UEnhancedInputComponent>(InputComponent))
    {
        UE_LOG(LogTemp, Warning, TEXT("P1_INPUT BLOCKED controller InputComponent is not EnhancedInputComponent"));
    }
    else
    {
        UE_LOG(LogTemp, Display, TEXT("P1_INPUT EnhancedInputComponent ready"));
    }
    InputComponent->BindAxis(TEXT("P1_RawAxis1"), this, &AP1InputValidationController::OnRawAxis1);
    InputComponent->BindAxis(TEXT("P1_RawAxis2"), this, &AP1InputValidationController::OnRawAxis2);
    InputComponent->BindAxis(TEXT("P1_RawAxis3"), this, &AP1InputValidationController::OnRawAxis3);
    InputComponent->BindAxis(TEXT("P1_RawAxis4"), this, &AP1InputValidationController::OnRawAxis4);
    InputComponent->BindAxis(TEXT("P1_RawAxis5"), this, &AP1InputValidationController::OnRawAxis5);
    InputComponent->BindAxis(TEXT("P1_RawAxis6"), this, &AP1InputValidationController::OnRawAxis6);
}
void AP1InputValidationController::OnRawAxis1(float Value){if(FMath::Abs(Value)>0.001f)UE_LOG(LogTemp,Display,TEXT("P1_RAW_AXIS axis=1 value=%.6f"),Value);}
void AP1InputValidationController::OnRawAxis2(float Value){if(FMath::Abs(Value)>0.001f)UE_LOG(LogTemp,Display,TEXT("P1_RAW_AXIS axis=2 value=%.6f"),Value);}
void AP1InputValidationController::OnRawAxis3(float Value){if(FMath::Abs(Value)>0.001f)UE_LOG(LogTemp,Display,TEXT("P1_RAW_AXIS axis=3 value=%.6f"),Value);}
void AP1InputValidationController::OnRawAxis4(float Value){if(FMath::Abs(Value)>0.001f)UE_LOG(LogTemp,Display,TEXT("P1_RAW_AXIS axis=4 value=%.6f"),Value);}
void AP1InputValidationController::OnRawAxis5(float Value){if(FMath::Abs(Value)>0.001f)UE_LOG(LogTemp,Display,TEXT("P1_RAW_AXIS axis=5 value=%.6f"),Value);}
void AP1InputValidationController::OnRawAxis6(float Value){if(FMath::Abs(Value)>0.001f)UE_LOG(LogTemp,Display,TEXT("P1_RAW_AXIS axis=6 value=%.6f"),Value);}

