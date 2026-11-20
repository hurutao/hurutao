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
};
