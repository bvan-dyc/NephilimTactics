#pragma once

#include "CoreMinimal.h"
#include "ArcEntityHandleInternal.h"

struct NEPHGLITTERTACTICS_API FNephBoardEvents
{
	TArray<TWeakObjectPtr<class ANephBoardActor>> BoardCreatedEvents;
	
	bool bRegenerateBoardCommand = false;
};
