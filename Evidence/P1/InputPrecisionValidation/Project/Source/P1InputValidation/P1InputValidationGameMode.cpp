#include "P1InputValidationGameMode.h"
#include "P1InputValidationController.h"
#include "InputPrecisionSampler.h"
#include "Engine/World.h"
AP1InputValidationGameMode::AP1InputValidationGameMode()
{
    PlayerControllerClass = AP1InputValidationController::StaticClass();
    DefaultPawnClass = nullptr;
}
void AP1InputValidationGameMode::BeginPlay()
{
    Super::BeginPlay();
    if (GetWorld())
    {
        GetWorld()->SpawnActor<AP1InputPrecisionSampler>(FVector::ZeroVector, FRotator::ZeroRotator);
    }
}

