#pragma once
#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "P1InputValidationController.generated.h"
UCLASS()
class AP1InputValidationController : public APlayerController
{
    GENERATED_BODY()
public:
    AP1InputValidationController();
    virtual void BeginPlay() override;
protected:
    virtual void SetupInputComponent() override;
private:
    void OnRawAxis1(float Value); void OnRawAxis2(float Value); void OnRawAxis3(float Value); void OnRawAxis4(float Value); void OnRawAxis5(float Value); void OnRawAxis6(float Value);
};
