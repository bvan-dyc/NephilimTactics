// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "NephCharacter.generated.h"

UCLASS()
class NEPHGLITTERTACTICS_API ANephCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	
	ANephCharacter();

	template<typename T>
	T* GetConfig()
	{
		return FindComponentByClass<T>();
	}
	
	// Called every frame.
	virtual void Tick(float DeltaSeconds) override;

	void MoveForward(float Value);
	void MoveRight(float Value);

	virtual void BeginPlay() override;
	
	/** Returns TopDownCameraComponent subobject **/
	FORCEINLINE class UCameraComponent* GetTopDownCameraComponent() const { return TopDownCameraComponent; }
	/** Returns CameraBoom subobject **/
	FORCEINLINE class USpringArmComponent* GetCameraBoom() const { return CameraBoom; }

private:

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class UCameraComponent* TopDownCameraComponent;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class USpringArmComponent* CameraBoom;
};

