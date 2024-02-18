#pragma once

#include "CoreMinimal.h"
#include "ArcEntityHandleInternal.h"

struct NEPHGLITTERTACTICS_API FNephUnitsEvents
{
	TArray<TPair<FArcEntityHandle, TWeakObjectPtr<class ANephCharacter>>> CharacterCreatedEvents;
	
	TArray<TPair<FArcEntityHandle, FIntPoint>> PlaceUnitOnTileCommands;
};
