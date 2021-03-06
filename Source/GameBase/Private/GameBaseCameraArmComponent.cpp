// Copyright (c) 2017, Peter Bačinský <peter@bacinsky.sk>

#include "GameBaseCameraArmComponent.h"
#include "Kismet/KismetMathLibrary.h"


// Initializer
UGameBaseCameraArmComponent::UGameBaseCameraArmComponent()
{
	// TODO?
	//bAbsoluteRotation = true;
}


// Update target arm length
void UGameBaseCameraArmComponent::UpdateTargetArmLength(float DeltaLength)
{
	float NewTargetArmLength = TargetArmLength + DeltaLength * UpdateDeltaLengthMultiplier;

	if (NewTargetArmLength >= MinTargetArmLength && NewTargetArmLength <= MaxTargetArmLength)
		TargetArmLength = NewTargetArmLength;
}


// Update camera rotation X
void UGameBaseCameraArmComponent::UpdateRelativeRotationX(float DeltaRotation)
{
	AddRelativeRotation(FRotator(0, DeltaRotation, 0));		
}


// Update camera rotation Y
void UGameBaseCameraArmComponent::UpdateRelativeRotationY(float DeltaRotation)
{
	FRotator NewRotation = RelativeRotation + FRotator(DeltaRotation, 0, 0);

	NewRotation.Roll  = 0;
	NewRotation.Pitch = UKismetMathLibrary::FClamp(NewRotation.Pitch, -85, 85);

	SetRelativeRotation(NewRotation);
}
