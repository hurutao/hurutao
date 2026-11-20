#include "P1InputValidationController.h"
#include "EnhancedInputComponent.h"
AP1InputValidationController::AP1InputValidationController() {}
void AP1InputValidationController::SetupInputComponent()
{
    Super::SetupInputComponent();
    if (!Cast<UEnhancedInputComponent>(InputComponent))
    {
        InputComponent = NewObject<UEnhancedInputComponent>(this, TEXT("P1EnhancedInputComponent"));
        InputComponent->RegisterComponent();
    }
    if (!Cast<UEnhancedInputComponent>(InputComponent))
    {
        UE_LOG(LogTemp, Warning, TEXT("P1_INPUT BLOCKED controller InputComponent is not EnhancedInputComponent"));
    }
}
