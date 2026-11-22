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
}

