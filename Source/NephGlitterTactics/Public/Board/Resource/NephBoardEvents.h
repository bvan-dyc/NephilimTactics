#pragma once

#include "CoreMinimal.h"
#include "ArcEntityHandleInternal.h"

struct NEPHGLITTERTACTICS_API FNephBoardEvents
{
	TArray<TPair<FArcEntityHandle, TWeakObjectPtr<class ANephBoardActor>>> BoardCreatedEvents;
};
