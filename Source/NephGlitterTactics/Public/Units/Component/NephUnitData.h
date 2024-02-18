#pragma once

#include "CoreMinimal.h"

#include "NephUnitData.generated.h"

USTRUCT()
struct FNephUnitData
{
	GENERATED_BODY()
    
public:

	~FNephUnitData();

	TWeakObjectPtr<class ANephCharacter> UnitActor;
};