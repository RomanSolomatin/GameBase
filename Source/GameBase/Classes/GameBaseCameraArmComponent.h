// Copyright (c) 2017, Peter Bačinský <peter@bacinsky.sk>

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/SpringArmComponent.h"
#include "GameBaseCameraArmComponent.generated.h"


/**
 * Enhanced camera arm component
 */
UCLASS(DisplayName = CameraArm, ClassGroup = (Custom), editinlinenew, meta = (BlueprintSpawnableComponent))
class GAMEBASE_API UGameBaseCameraArmComponent : public USpringArmComponent
{
	GENERATED_BODY()

public:
	// Initializer
	UGameBaseCameraArmComponent();

	// Update target arm length
	UFUNCTION(BlueprintCallable, Category = CameraArm)
	void UpdateTargetArmLength(float DeltaLength);

	// Update camera rotation X
	UFUNCTION(BlueprintCallable, Category = CameraArm)
	void UpdateRelativeRotationX(float DeltaRotation);

	// Update camera rotation Y
	UFUNCTION(BlueprintCallable, Category = CameraArm)
	void UpdateRelativeRotationY(float DeltaRotation);

	// Min target arm length
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = CameraArm)
	float MinTargetArmLength = 100;

	// Max target arm length
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = CameraArm)
	float MaxTargetArmLength = 1000;

	// Update target arm length multiplier
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = CameraArm)
	float UpdateDeltaLengthMultiplier = 10;
};
