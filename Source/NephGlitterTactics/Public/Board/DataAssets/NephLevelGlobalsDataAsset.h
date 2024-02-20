#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "Board/Resource/NephLevelGlobals.h"
#include "NephLevelGlobalsDataAsset.generated.h"

UCLASS()
class NEPHGLITTERTACTICS_API UNephLevelGlobalsDataAsset : public UDataAsset
{
	GENERATED_BODY()
	
public:

	UPROPERTY(EditDefaultsOnly, meta = (ShowOnlyInnerProperties))
	FNephLevelGlobals LevelGlobals;
};
