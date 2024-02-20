#pragma once

#include "Engine/DataAsset.h"

#include "NephUnitClassDataAsset.generated.h"

UCLASS()
class NEPHGLITTERTACTICS_API UNephUnitClassDataAsset : public UDataAsset
{
	GENERATED_BODY()

public:

	UPROPERTY(EditAnywhere)
	FText ClassName = FText::GetEmpty(); 
};
