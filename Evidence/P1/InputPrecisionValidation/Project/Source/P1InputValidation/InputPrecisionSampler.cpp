#include "InputPrecisionSampler.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "InputActionValue.h"
#include "InputMappingContext.h"
#include "InputModifiers.h"
#include "InputCoreTypes.h"
#include "GameFramework/PlayerController.h"
#include "Engine/LocalPlayer.h"
#include "Engine/World.h"
#include "Misc/FileHelper.h"
#include "Misc/Paths.h"
AP1InputPrecisionSampler::AP1InputPrecisionSampler(){PrimaryActorTick.bCanEverTick=true;}
void AP1InputPrecisionSampler::BeginPlay(){Super::BeginPlay(); CreateRuntimeMapping(); BindInput();}
void AP1InputPrecisionSampler::CreateRuntimeMapping(){
 if(MappingContext)return;
 MappingContext=NewObject<UInputMappingContext>(this);
 LeftStickAction=NewObject<UInputAction>(this); LeftStickAction->ValueType=EInputActionValueType::Axis2D;
 RightStickAction=NewObject<UInputAction>(this); RightStickAction->ValueType=EInputActionValueType::Axis2D;
 LeftTriggerAction=NewObject<UInputAction>(this); LeftTriggerAction->ValueType=EInputActionValueType::Axis1D;
 RightTriggerAction=NewObject<UInputAction>(this); RightTriggerAction->ValueType=EInputActionValueType::Axis1D;
 MappingContext->MapKey(LeftStickAction,EKeys::Gamepad_LeftX);
 FEnhancedActionKeyMapping& LSY=MappingContext->MapKey(LeftStickAction,EKeys::Gamepad_LeftY); UInputModifierSwizzleAxis* LSw=NewObject<UInputModifierSwizzleAxis>(this); LSw->Order=EInputAxisSwizzle::YXZ; LSY.Modifiers.Add(LSw);
 MappingContext->MapKey(RightStickAction,EKeys::Gamepad_RightX);
 FEnhancedActionKeyMapping& RSY=MappingContext->MapKey(RightStickAction,EKeys::Gamepad_RightY); UInputModifierSwizzleAxis* RSw=NewObject<UInputModifierSwizzleAxis>(this); RSw->Order=EInputAxisSwizzle::YXZ; RSY.Modifiers.Add(RSw);
 MappingContext->MapKey(LeftTriggerAction,EKeys::Gamepad_LeftTriggerAxis);
 MappingContext->MapKey(RightTriggerAction,EKeys::Gamepad_RightTriggerAxis);
}

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
 FVector3f P=FVector3f::ZeroVector;
 const FString ActionName(Name);
 if(ActionName==TEXT("LT_L2") || ActionName==TEXT("RT_R2")){ P.X=V.Get<float>(); } else { const FVector2D Stick=V.Get<FVector2D>(); P.X=Stick.X; P.Y=Stick.Y; }
 const FVector2f Raw(P.X,P.Y); const FVector2f A=ApplyAxial(Raw); const FVector2f R=ApplyRadial(Raw);
 const FString NewLine=FString::Printf(TEXT("Unknown,Unknown,%s,%.6f,,,,%.6f,%.6f,%.6f,%.6f,%.6f,%.6f,%.6f,,%d,UNVERIFIED\n"),Name,GetWorld()->GetTimeSeconds(),P.X,P.Y,P.Z,A.X,A.Y,R.X,R.Y,DuplicateCount);
 const FString CsvPath=FPaths::ProjectSavedDir()/TEXT("P1InputSamples.csv");
 if(!FPaths::FileExists(CsvPath)){FFileHelper::SaveStringToFile(TEXT("device,connection,action,timestamp_seconds,raw_x,raw_y,raw_z,processed_x,processed_y,processed_z,axial_x,axial_y,radial_x,radial_y,button_state,duplicate_count,raw_layer_status\n"),*CsvPath);}
 FFileHelper::SaveStringToFile(NewLine,*CsvPath, FFileHelper::EEncodingOptions::AutoDetect, &IFileManager::Get(), FILEWRITE_Append);
 UE_LOG(LogTemp,Display,TEXT("P1_INPUT_SAMPLE action=%s time=%.6f processed=(%.6f,%.6f,%.6f) axial=(%.6f,%.6f) radial=(%.6f,%.6f) raw_layer=UNVERIFIED"),Name,GetWorld()->GetTimeSeconds(),P.X,P.Y,P.Z,A.X,A.Y,R.X,R.Y);
}
FVector2f AP1InputPrecisionSampler::ApplyAxial(const FVector2f& V)const{return FVector2f(FMath::Abs(V.X)<AxialDeadZone?0.f:V.X,FMath::Abs(V.Y)<AxialDeadZone?0.f:V.Y);}
FVector2f AP1InputPrecisionSampler::ApplyRadial(const FVector2f& V)const{const float M=V.Size();if(M<RadialDeadZone)return FVector2f::ZeroVector;FVector2f Result=V.GetSafeNormal()*((M-RadialDeadZone)/(1.f-RadialDeadZone)); Result.X=FMath::Clamp(Result.X,-1.f,1.f); Result.Y=FMath::Clamp(Result.Y,-1.f,1.f); return Result;}








