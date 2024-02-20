#pragma once

#include "Engine/DataAsset.h"

#include "NephCharacterDataAsset.generated.h"

UCLASS()
class NEPHGLITTERTACTICS_API UNephCharacterDataAsset : public UDataAsset
{
	GENERATED_BODY()

public:

	UPROPERTY(EditAnywhere)
	FText CharacterName = FText::GetEmpty(); 
};
