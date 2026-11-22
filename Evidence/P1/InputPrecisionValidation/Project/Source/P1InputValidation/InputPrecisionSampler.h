#pragma once
#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "InputPrecisionSampler.generated.h"
class UInputAction;
class UInputMappingContext;
class UEnhancedInputComponent;
UCLASS()
class AP1InputPrecisionSampler : public AActor
{
    GENERATED_BODY()
public:
    AP1InputPrecisionSampler();
    virtual void BeginPlay() override;
    virtual void Tick(float DeltaSeconds) override;
    UPROPERTY(EditAnywhere, Category="P1 Input Validation") TObjectPtr<UInputMappingContext> MappingContext;
    UPROPERTY(EditAnywhere, Category="P1 Input Validation") TObjectPtr<UInputAction> LeftStickAction;
    UPROPERTY(EditAnywhere, Category="P1 Input Validation") TObjectPtr<UInputAction> RightStickAction;
    UPROPERTY(EditAnywhere, Category="P1 Input Validation") TObjectPtr<UInputAction> LeftTriggerAction;
    UPROPERTY(EditAnywhere, Category="P1 Input Validation") TObjectPtr<UInputAction> RightTriggerAction;
    UPROPERTY() TObjectPtr<UInputAction> RawAxisActions[6];
    UPROPERTY() TObjectPtr<UInputAction> ButtonActions[10];
    UPROPERTY(EditAnywhere, Category="P1 Input Validation") float AxialDeadZone = 0.12f;
    UPROPERTY(EditAnywhere, Category="P1 Input Validation") float RadialDeadZone = 0.12f;
private:
    void CreateRuntimeMapping();
    void BindInput();
    void OnLeftStick(const struct FInputActionValue& Value);
    void OnRightStick(const struct FInputActionValue& Value);
    void OnLeftTrigger(const struct FInputActionValue& Value);
    void OnRightTrigger(const struct FInputActionValue& Value);
    void OnRawAxis1(const struct FInputActionValue& Value); void OnRawAxis2(const struct FInputActionValue& Value); void OnRawAxis3(const struct FInputActionValue& Value); void OnRawAxis4(const struct FInputActionValue& Value); void OnRawAxis5(const struct FInputActionValue& Value); void OnRawAxis6(const struct FInputActionValue& Value);
    void OnButtonA(const struct FInputActionValue& Value); void OnButtonB(const struct FInputActionValue& Value); void OnButtonX(const struct FInputActionValue& Value); void OnButtonY(const struct FInputActionValue& Value); void OnButtonLB(const struct FInputActionValue& Value); void OnButtonRB(const struct FInputActionValue& Value); void OnButtonView(const struct FInputActionValue& Value); void OnButtonMenu(const struct FInputActionValue& Value); void OnButtonLS(const struct FInputActionValue& Value); void OnButtonRS(const struct FInputActionValue& Value);
    void Record(const TCHAR* ActionName, const struct FInputActionValue& Value);
    void RecordButton(const TCHAR* ActionName, const struct FInputActionValue& Value);
    FVector2f ApplyAxial(const FVector2f& Value) const;
    FVector2f ApplyRadial(const FVector2f& Value) const;
    TSet<FString> ActionsThisFrame;
    int32 DuplicateCount = 0;
};


