// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "NephCameraActor.generated.h"

UCLASS()
class NEPHGLITTERTACTICS_API ANephCameraActor: public APawn
{
	GENERATED_BODY()

public:
	
	ANephCameraActor();

	// Called every frame.
	virtual void Tick(float DeltaSeconds) override;

	void MoveForward(float Value);
	void MoveRight(float Value);
	
	/** Returns TopDownCameraComponent subobject **/
	FORCEINLINE class UCameraComponent* GetTopDownCameraComponent() const { return TopDownCameraComponent; }
	/** Returns CameraBoom subobject **/
	FORCEINLINE class USpringArmComponent* GetCameraBoom() const { return CameraBoom; }

private:

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class UCameraComponent* TopDownCameraComponent;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class USpringArmComponent* CameraBoom;

	UPROPERTY()
	UCapsuleComponent* CapsuleComponent;

	UPROPERTY(EditAnywhere)
	float CameraMoveSpeed = 50.f;
};

