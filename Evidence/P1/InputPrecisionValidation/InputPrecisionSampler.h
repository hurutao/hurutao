#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "InputPrecisionSampler.generated.h"

class UInputAction;
class UInputMappingContext;
class UEnhancedInputComponent;

UCLASS()
class AInputPrecisionSampler : public AActor
{
    GENERATED_BODY()

public:
    AInputPrecisionSampler();

    virtual void BeginPlay() override;
    virtual void Tick(float DeltaSeconds) override;

    UPROPERTY(EditAnywhere, Category="P1 Input Validation")
    TObjectPtr<UInputMappingContext> MappingContext;

    UPROPERTY(EditAnywhere, Category="P1 Input Validation")
    TObjectPtr<UInputAction> MoveAction;

    UPROPERTY(EditAnywhere, Category="P1 Input Validation")
    TObjectPtr<UInputAction> LookAction;

    UPROPERTY(EditAnywhere, Category="P1 Input Validation")
    TObjectPtr<UInputAction> LeftTriggerAction;

    UPROPERTY(EditAnywhere, Category="P1 Input Validation")
    TObjectPtr<UInputAction> RightTriggerAction;

    UPROPERTY(EditAnywhere, Category="P1 Input Validation")
    float AxialDeadZone = 0.12f;

    UPROPERTY(EditAnywhere, Category="P1 Input Validation")
    float RadialDeadZone = 0.12f;

private:
    void BindEnhancedInput();
    void SampleAction(const TCHAR* ActionName, const FVector3f& ProcessedValue, double CallbackTime);
    FVector2f ApplyAxialDeadZone(const FVector2f& Value) const;
    FVector2f ApplyRadialDeadZone(const FVector2f& Value) const;
    void WriteCsvRow(const TCHAR* ActionName, const FVector3f& ProcessedValue, double CallbackTime);

    TSet<FString> ActionsSeenThisFrame;
    int32 DuplicateCallbackCount = 0;
};
