#include "InputPrecisionSampler.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "InputActionValue.h"
#include "InputMappingContext.h"
#include "GameFramework/PlayerController.h"
#include "Engine/LocalPlayer.h"
#include "Engine/World.h"
AP1InputPrecisionSampler::AP1InputPrecisionSampler(){PrimaryActorTick.bCanEverTick=true;}
void AP1InputPrecisionSampler::BeginPlay(){Super::BeginPlay(); BindInput();}
void AP1InputPrecisionSampler::BindInput(){
 APlayerController* PC=GetWorld()->GetFirstPlayerController(); if(!PC){UE_LOG(LogTemp,Warning,TEXT("P1_INPUT BLOCKED no PlayerController"));return;}
 if(MappingContext){if(ULocalPlayer* LP=PC->GetLocalPlayer()){if(UEnhancedInputLocalPlayerSubsystem* S=LP->GetSubsystem<UEnhancedInputLocalPlayerSubsystem>()){S->AddMappingContext(MappingContext,100);}}}
 UEnhancedInputComponent* EIC=Cast<UEnhancedInputComponent>(PC->InputComponent); if(!EIC){UE_LOG(LogTemp,Warning,TEXT("P1_INPUT BLOCKED no EnhancedInputComponent"));return;}
 if(LeftStickAction)EIC->BindAction(LeftStickAction,ETriggerEvent::Triggered,this,&AP1InputPrecisionSampler::OnLeftStick);
 if(RightStickAction)EIC->BindAction(RightStickAction,ETriggerEvent::Triggered,this,&AP1InputPrecisionSampler::OnRightStick);
 if(LeftTriggerAction)EIC->BindAction(LeftTriggerAction,ETriggerEvent::Triggered,this,&AP1InputPrecisionSampler::OnLeftTrigger);
 if(RightTriggerAction)EIC->BindAction(RightTriggerAction,ETriggerEvent::Triggered,this,&AP1InputPrecisionSampler::OnRightTrigger);
}
void AP1InputPrecisionSampler::OnLeftStick(const FInputActionValue& V){Record(TEXT("LeftStick"),V);}
void AP1InputPrecisionSampler::OnRightStick(const FInputActionValue& V){Record(TEXT("RightStick"),V);}
void AP1InputPrecisionSampler::OnLeftTrigger(const FInputActionValue& V){Record(TEXT("LT_L2"),V);}
void AP1InputPrecisionSampler::OnRightTrigger(const FInputActionValue& V){Record(TEXT("RT_R2"),V);}
void AP1InputPrecisionSampler::Record(const TCHAR* Name,const FInputActionValue& V){
 const FString Action(Name); if(ActionsThisFrame.Contains(Action)){DuplicateCount++;UE_LOG(LogTemp,Warning,TEXT("P1_INPUT DUPLICATE action=%s count=%d"),Name,DuplicateCount);} ActionsThisFrame.Add(Action);
 const FVector P3=V.Get<FVector>(); const FVector3f P(P3); const FVector2f Raw(P.X,P.Y); const FVector2f A=ApplyAxial(Raw); const FVector2f R=ApplyRadial(Raw);
 UE_LOG(LogTemp,Display,TEXT("P1_INPUT_SAMPLE action=%s time=%.6f processed=(%.6f,%.6f,%.6f) axial=(%.6f,%.6f) radial=(%.6f,%.6f) raw_layer=UNVERIFIED"),Name,GetWorld()->GetTimeSeconds(),P.X,P.Y,P.Z,A.X,A.Y,R.X,R.Y);
}
FVector2f AP1InputPrecisionSampler::ApplyAxial(const FVector2f& V)const{return FVector2f(FMath::Abs(V.X)<AxialDeadZone?0.f:V.X,FMath::Abs(V.Y)<AxialDeadZone?0.f:V.Y);}
FVector2f AP1InputPrecisionSampler::ApplyRadial(const FVector2f& V)const{const float M=V.Size();if(M<RadialDeadZone)return FVector2f::ZeroVector;return V.GetSafeNormal()*((M-RadialDeadZone)/(1.f-RadialDeadZone));}

