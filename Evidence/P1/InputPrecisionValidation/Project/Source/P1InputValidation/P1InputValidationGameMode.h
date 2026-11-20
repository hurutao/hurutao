#pragma once
#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "P1InputValidationGameMode.generated.h"
UCLASS()
class AP1InputValidationGameMode : public AGameModeBase
{
    GENERATED_BODY()
public:
    AP1InputValidationGameMode();
    virtual void BeginPlay() override;
};

