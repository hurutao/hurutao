#include "InputPrecisionSampler.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "InputAction.h"
#include "InputMappingContext.h"
#include "GameFramework/PlayerController.h"
#include "Engine/World.h"

AInputPrecisionSampler::AInputPrecisionSampler()
{
    PrimaryActorTick.bCanEverTick = true;
}

void AInputPrecisionSampler::BeginPlay()
{
    Super::BeginPlay();
    BindEnhancedInput();
}

void AInputPrecisionSampler::BindEnhancedInput()
{
    APlayerController* PlayerController = GetWorld()->GetFirstPlayerController();
    if (!PlayerController || !MappingContext)
    {
        UE_LOG(LogTemp, Warning, TEXT("P1_INPUT BLOCKED missing PlayerController or MappingContext"));
        return;
    }

    if (ULocalPlayer* LocalPlayer = PlayerController->GetLocalPlayer())
    {
        if (UEnhancedInputLocalPlayerSubsystem* Subsystem =
            LocalPlayer->GetSubsystem<UEnhancedInputLocalPlayerSubsystem>())
        {
            Subsystem->AddMappingContext(MappingContext, 100);
        }
    }

    UEnhancedInputComponent* InputComponent = Cast<UEnhancedInputComponent>(PlayerController->InputComponent);
    if (!InputComponent)
    {
        UE_LOG(LogTemp, Warning, TEXT("P1_INPUT BLOCKED EnhancedInputComponent unavailable"));
        return;
    }

    if (MoveAction)
    {
        InputComponent->BindAction(MoveAction, ETriggerEvent::Triggered, this,
            &AInputPrecisionSampler::SampleAction, TEXT("Move"));
    }
    if (LookAction)
    {
        InputComponent->BindAction(LookAction, ETriggerEvent::Triggered, this,
            &AInputPrecisionSampler::SampleAction, TEXT("Look"));
    }
    if (LeftTriggerAction)
    {
        InputComponent->BindAction(LeftTriggerAction, ETriggerEvent::Triggered, this,
            &AInputPrecisionSampler::SampleAction, TEXT("LT_L2"));
    }
    if (RightTriggerAction)
    {
        InputComponent->BindAction(RightTriggerAction, ETriggerEvent::Triggered, this,
            &AInputPrecisionSampler::SampleAction, TEXT("RT_R2"));
    }
}

void AInputPrecisionSampler::Tick(float DeltaSeconds)
{
    Super::Tick(DeltaSeconds);
    ActionsSeenThisFrame.Reset();
}

void AInputPrecisionSampler::SampleAction(const TCHAR* ActionName,
    const FVector3f& ProcessedValue, double CallbackTime)
{
    const FString Name(ActionName);
    if (ActionsSeenThisFrame.Contains(Name))
    {
        ++DuplicateCallbackCount;
        UE_LOG(LogTemp, Warning, TEXT("P1_INPUT DUPLICATE action=%s count=%d"), ActionName, DuplicateCallbackCount);
    }
    ActionsSeenThisFrame.Add(Name);
    WriteCsvRow(ActionName, ProcessedValue, CallbackTime);
}

FVector2f AInputPrecisionSampler::ApplyAxialDeadZone(const FVector2f& Value) const
{
    return FVector2f(
        FMath::Abs(Value.X) < AxialDeadZone ? 0.0f : Value.X,
        FMath::Abs(Value.Y) < AxialDeadZone ? 0.0f : Value.Y);
}

FVector2f AInputPrecisionSampler::ApplyRadialDeadZone(const FVector2f& Value) const
{
    const float Magnitude = Value.Size();
    if (Magnitude < RadialDeadZone)
    {
        return FVector2f::ZeroVector;
    }
    return Value.GetSafeNormal() * ((Magnitude - RadialDeadZone) / (1.0f - RadialDeadZone));
}

void AInputPrecisionSampler::WriteCsvRow(const TCHAR* ActionName,
    const FVector3f& ProcessedValue, double CallbackTime)
{
    const FVector2f Raw2D(ProcessedValue.X, ProcessedValue.Y);
    const FVector2f Axial = ApplyAxialDeadZone(Raw2D);
    const FVector2f Radial = ApplyRadialDeadZone(Raw2D);
    UE_LOG(LogTemp, Display,
        TEXT("P1_INPUT_SAMPLE action=%s time=%.6f processed=(%.6f,%.6f,%.6f) axial=(%.6f,%.6f) radial=(%.6f,%.6f) raw_source=UNVERIFIED"),
        ActionName, CallbackTime, ProcessedValue.X, ProcessedValue.Y, ProcessedValue.Z,
        Axial.X, Axial.Y, Radial.X, Radial.Y);
}
