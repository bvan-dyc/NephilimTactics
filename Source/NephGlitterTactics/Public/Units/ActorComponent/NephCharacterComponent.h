#pragma once

#include "CoreMinimal.h"

#include "ActorComponent/ArcBaseComponent.h"
#include "Units/Component/NephUnitData.h"

#include "NephCharacterComponent.generated.h"

UCLASS(ClassGroup = "ArcECS", meta = (BlueprintSpawnableComponent))
class NEPHGLITTERTACTICS_API UNephCharacterComponent : public UArcBaseComponent
{
	GENERATED_BODY()
	
public:

	UPROPERTY(EditAnywhere, meta = (ShowOnlyInnerProperties))
	FNephUnitData Data;

	UPROPERTY(EditAnywhere)
	class USkeletalMesh* Skeleton = nullptr;
	
	UPROPERTY(EditAnywhere)
	TSubclassOf<class UAnimInstance> AnimInstance = nullptr;
public:

	UNephCharacterComponent();
	
	virtual void AddComponentsToEntity(FArcUniverse& Universe, FArcEntityHandle& Entity) override;
	virtual void RemoveComponentsFromEntity(FArcUniverse& Universe, FArcEntityHandle& Entity) override;
	
	virtual void OnRegister() override;
	virtual void OnUnregister() override;
};