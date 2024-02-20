#pragma once

#include "CoreMinimal.h"
#include "NephLevelGlobals.generated.h"

USTRUCT()
struct FNephLevelGlobals
{
	GENERATED_BODY()

public:

	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<class AActor> TileSelectorClass = nullptr;
};
