#pragma once

#include "GameplayTagContainer.h"

#include "NephBattleController.generated.h"

USTRUCT()
struct NEPHGLITTERTACTICS_API FNephBattleController
{
	GENERATED_BODY()

public:

    FGameplayTag CurrentBattleState;
};
