#include "InputPrecisionSampler.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "InputActionValue.h"
#include "InputMappingContext.h"
#include "InputModifiers.h"
#include "InputCoreTypes.h"
#include "RawInputFunctionLibrary.h"
#include "GameFramework/PlayerController.h"
#include "Engine/LocalPlayer.h"
#include "Engine/World.h"
#include "Misc/FileHelper.h"
#include "Misc/Paths.h"
AP1InputPrecisionSampler::AP1InputPrecisionSampler(){PrimaryActorTick.bCanEverTick=true;}
void AP1InputPrecisionSampler::BeginPlay(){Super::BeginPlay(); CreateRuntimeMapping(); BindInput();}
void AP1InputPrecisionSampler::Tick(float DeltaSeconds){Super::Tick(DeltaSeconds); ActionsThisFrame.Reset();}
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
 const FKey RawKeys[6]={FRawInputKeys::GenericUSBController_Axis1,FRawInputKeys::GenericUSBController_Axis2,FRawInputKeys::GenericUSBController_Axis3,FRawInputKeys::GenericUSBController_Axis4,FRawInputKeys::GenericUSBController_Axis5,FRawInputKeys::GenericUSBController_Axis6};
 for(int32 Index=0;Index<6;++Index){RawAxisActions[Index]=NewObject<UInputAction>(this);RawAxisActions[Index]->ValueType=EInputActionValueType::Axis1D;MappingContext->MapKey(RawAxisActions[Index],RawKeys[Index]);}
 const FKey ButtonKeys[10]={EKeys::Gamepad_FaceButton_Bottom,EKeys::Gamepad_FaceButton_Right,EKeys::Gamepad_FaceButton_Left,EKeys::Gamepad_FaceButton_Top,EKeys::Gamepad_LeftShoulder,EKeys::Gamepad_RightShoulder,EKeys::Gamepad_Special_Left,EKeys::Gamepad_Special_Right,EKeys::Gamepad_LeftThumbstick,EKeys::Gamepad_RightThumbstick};
 for(int32 Index=0;Index<10;++Index){ButtonActions[Index]=NewObject<UInputAction>(this);ButtonActions[Index]->ValueType=EInputActionValueType::Boolean;MappingContext->MapKey(ButtonActions[Index],ButtonKeys[Index]);}
}

void AP1InputPrecisionSampler::BindInput(){
 APlayerController* PC=GetWorld()->GetFirstPlayerController(); if(!PC){UE_LOG(LogTemp,Warning,TEXT("P1_INPUT BLOCKED no PlayerController"));return;}
 if(MappingContext){if(ULocalPlayer* LP=PC->GetLocalPlayer()){if(UEnhancedInputLocalPlayerSubsystem* S=LP->GetSubsystem<UEnhancedInputLocalPlayerSubsystem>()){S->AddMappingContext(MappingContext,100);}}}
 UEnhancedInputComponent* EIC=Cast<UEnhancedInputComponent>(PC->InputComponent); if(!EIC){UE_LOG(LogTemp,Warning,TEXT("P1_INPUT BLOCKED no EnhancedInputComponent"));return;}
 UE_LOG(LogTemp,Display,TEXT("P1_INPUT binding runtime actions"));
 if(LeftStickAction)EIC->BindAction(LeftStickAction,ETriggerEvent::Triggered,this,&AP1InputPrecisionSampler::OnLeftStick);
 if(RightStickAction)EIC->BindAction(RightStickAction,ETriggerEvent::Triggered,this,&AP1InputPrecisionSampler::OnRightStick);
 if(LeftTriggerAction)EIC->BindAction(LeftTriggerAction,ETriggerEvent::Triggered,this,&AP1InputPrecisionSampler::OnLeftTrigger);
 if(RightTriggerAction)EIC->BindAction(RightTriggerAction,ETriggerEvent::Triggered,this,&AP1InputPrecisionSampler::OnRightTrigger);
 if(RawAxisActions[0])EIC->BindAction(RawAxisActions[0],ETriggerEvent::Triggered,this,&AP1InputPrecisionSampler::OnRawAxis1); if(RawAxisActions[1])EIC->BindAction(RawAxisActions[1],ETriggerEvent::Triggered,this,&AP1InputPrecisionSampler::OnRawAxis2); if(RawAxisActions[2])EIC->BindAction(RawAxisActions[2],ETriggerEvent::Triggered,this,&AP1InputPrecisionSampler::OnRawAxis3); if(RawAxisActions[3])EIC->BindAction(RawAxisActions[3],ETriggerEvent::Triggered,this,&AP1InputPrecisionSampler::OnRawAxis4); if(RawAxisActions[4])EIC->BindAction(RawAxisActions[4],ETriggerEvent::Triggered,this,&AP1InputPrecisionSampler::OnRawAxis5); if(RawAxisActions[5])EIC->BindAction(RawAxisActions[5],ETriggerEvent::Triggered,this,&AP1InputPrecisionSampler::OnRawAxis6);
 if(ButtonActions[0])EIC->BindAction(ButtonActions[0],ETriggerEvent::Triggered,this,&AP1InputPrecisionSampler::OnButtonA); if(ButtonActions[1])EIC->BindAction(ButtonActions[1],ETriggerEvent::Triggered,this,&AP1InputPrecisionSampler::OnButtonB); if(ButtonActions[2])EIC->BindAction(ButtonActions[2],ETriggerEvent::Triggered,this,&AP1InputPrecisionSampler::OnButtonX); if(ButtonActions[3])EIC->BindAction(ButtonActions[3],ETriggerEvent::Triggered,this,&AP1InputPrecisionSampler::OnButtonY); if(ButtonActions[4])EIC->BindAction(ButtonActions[4],ETriggerEvent::Triggered,this,&AP1InputPrecisionSampler::OnButtonLB); if(ButtonActions[5])EIC->BindAction(ButtonActions[5],ETriggerEvent::Triggered,this,&AP1InputPrecisionSampler::OnButtonRB); if(ButtonActions[6])EIC->BindAction(ButtonActions[6],ETriggerEvent::Triggered,this,&AP1InputPrecisionSampler::OnButtonView); if(ButtonActions[7])EIC->BindAction(ButtonActions[7],ETriggerEvent::Triggered,this,&AP1InputPrecisionSampler::OnButtonMenu); if(ButtonActions[8])EIC->BindAction(ButtonActions[8],ETriggerEvent::Triggered,this,&AP1InputPrecisionSampler::OnButtonLS); if(ButtonActions[9])EIC->BindAction(ButtonActions[9],ETriggerEvent::Triggered,this,&AP1InputPrecisionSampler::OnButtonRS);
}
void AP1InputPrecisionSampler::OnLeftStick(const FInputActionValue& V){Record(TEXT("LeftStick"),V);}
void AP1InputPrecisionSampler::OnRightStick(const FInputActionValue& V){Record(TEXT("RightStick"),V);}
void AP1InputPrecisionSampler::OnLeftTrigger(const FInputActionValue& V){Record(TEXT("LT_L2"),V);}
void AP1InputPrecisionSampler::OnRightTrigger(const FInputActionValue& V){Record(TEXT("RT_R2"),V);}
void AP1InputPrecisionSampler::OnRawAxis1(const FInputActionValue& V){Record(TEXT("RawAxis1"),V);} void AP1InputPrecisionSampler::OnRawAxis2(const FInputActionValue& V){Record(TEXT("RawAxis2"),V);} void AP1InputPrecisionSampler::OnRawAxis3(const FInputActionValue& V){Record(TEXT("RawAxis3"),V);} void AP1InputPrecisionSampler::OnRawAxis4(const FInputActionValue& V){Record(TEXT("RawAxis4"),V);} void AP1InputPrecisionSampler::OnRawAxis5(const FInputActionValue& V){Record(TEXT("RawAxis5"),V);} void AP1InputPrecisionSampler::OnRawAxis6(const FInputActionValue& V){Record(TEXT("RawAxis6"),V);}
void AP1InputPrecisionSampler::OnButtonA(const FInputActionValue& V){RecordButton(TEXT("A"),V);} void AP1InputPrecisionSampler::OnButtonB(const FInputActionValue& V){RecordButton(TEXT("B"),V);} void AP1InputPrecisionSampler::OnButtonX(const FInputActionValue& V){RecordButton(TEXT("X"),V);} void AP1InputPrecisionSampler::OnButtonY(const FInputActionValue& V){RecordButton(TEXT("Y"),V);} void AP1InputPrecisionSampler::OnButtonLB(const FInputActionValue& V){RecordButton(TEXT("LB"),V);} void AP1InputPrecisionSampler::OnButtonRB(const FInputActionValue& V){RecordButton(TEXT("RB"),V);} void AP1InputPrecisionSampler::OnButtonView(const FInputActionValue& V){RecordButton(TEXT("View"),V);} void AP1InputPrecisionSampler::OnButtonMenu(const FInputActionValue& V){RecordButton(TEXT("Menu"),V);} void AP1InputPrecisionSampler::OnButtonLS(const FInputActionValue& V){RecordButton(TEXT("LS"),V);} void AP1InputPrecisionSampler::OnButtonRS(const FInputActionValue& V){RecordButton(TEXT("RS"),V);}
void AP1InputPrecisionSampler::RecordButton(const TCHAR* Name,const FInputActionValue& V){
 const bool Pressed=V.Get<bool>(); const FString CsvPath=FPaths::ProjectSavedDir()/TEXT("P1InputSamples.csv"); const FString NewLine=FString::Printf(TEXT("Unknown,Unknown,%s,%.6f,0.000000,0.000000,0.000000,0.000000,0.000000,0.000000,0.000000,0.000000,0.000000,0.000000,%d,%d,UNVERIFIED\n"),Name,GetWorld()->GetTimeSeconds(),Pressed?1:0,DuplicateCount); FFileHelper::SaveStringToFile(NewLine,*CsvPath,FFileHelper::EEncodingOptions::AutoDetect,&IFileManager::Get(),FILEWRITE_Append); UE_LOG(LogTemp,Display,TEXT("P1_INPUT_BUTTON action=%s pressed=%d raw_layer=UNVERIFIED"),Name,Pressed?1:0);
}
void AP1InputPrecisionSampler::Record(const TCHAR* Name,const FInputActionValue& V){
 const FString Action(Name); if(ActionsThisFrame.Contains(Action)){DuplicateCount++;UE_LOG(LogTemp,Warning,TEXT("P1_INPUT DUPLICATE action=%s count=%d"),Name,DuplicateCount);} ActionsThisFrame.Add(Action);
 FVector3f P=FVector3f::ZeroVector;
 const FString ActionName(Name);
 const bool bTrigger=ActionName==TEXT("LT_L2") || ActionName==TEXT("RT_R2");
 if(bTrigger || ActionName.StartsWith(TEXT("RawAxis"))){ P.X=V.Get<float>(); } else { const FVector2D Stick=V.Get<FVector2D>(); P.X=Stick.X; P.Y=Stick.Y; }
 FVector3f Processed=P;
 if(bTrigger){Processed.X=FMath::Clamp(P.X,0.f,1.f);}
 const FVector2f Raw(P.X,P.Y); const FVector2f Processed2(Processed.X,Processed.Y); const FVector2f A=ApplyAxial(Processed2); const FVector2f R=ApplyRadial(Processed2);
 const FString NewLine=FString::Printf(TEXT("Unknown,Unknown,%s,%.6f,%.6f,%.6f,%.6f,%.6f,%.6f,%.6f,%.6f,%.6f,%.6f,%.6f,,%d,UNVERIFIED\n"),Name,GetWorld()->GetTimeSeconds(),P.X,P.Y,P.Z,Processed.X,Processed.Y,Processed.Z,A.X,A.Y,R.X,R.Y,DuplicateCount);
 const FString CsvPath=FPaths::ProjectSavedDir()/TEXT("P1InputSamples.csv");
 if(!FPaths::FileExists(CsvPath)){FFileHelper::SaveStringToFile(TEXT("device,connection,action,timestamp_seconds,raw_x,raw_y,raw_z,processed_x,processed_y,processed_z,axial_x,axial_y,radial_x,radial_y,button_state,duplicate_count,raw_layer_status\n"),*CsvPath);}
 FFileHelper::SaveStringToFile(NewLine,*CsvPath, FFileHelper::EEncodingOptions::AutoDetect, &IFileManager::Get(), FILEWRITE_Append);
 UE_LOG(LogTemp,Display,TEXT("P1_INPUT_SAMPLE action=%s time=%.6f raw=(%.6f,%.6f,%.6f) processed=(%.6f,%.6f,%.6f) axial=(%.6f,%.6f) radial=(%.6f,%.6f) raw_layer=UNVERIFIED"),Name,GetWorld()->GetTimeSeconds(),P.X,P.Y,P.Z,Processed.X,Processed.Y,Processed.Z,A.X,A.Y,R.X,R.Y);
}
FVector2f AP1InputPrecisionSampler::ApplyAxial(const FVector2f& V)const{return FVector2f(FMath::Abs(V.X)<AxialDeadZone?0.f:V.X,FMath::Abs(V.Y)<AxialDeadZone?0.f:V.Y);}
FVector2f AP1InputPrecisionSampler::ApplyRadial(const FVector2f& V)const{const float M=V.Size();if(M<RadialDeadZone)return FVector2f::ZeroVector;FVector2f Result=V.GetSafeNormal()*((M-RadialDeadZone)/(1.f-RadialDeadZone)); Result.X=FMath::Clamp(Result.X,-1.f,1.f); Result.Y=FMath::Clamp(Result.Y,-1.f,1.f); return Result;}









