#pragma once
#include "GameplayTagContainer.h"

#include "NephBattleControllerEvents.generated.h"

struct FNephStateChangeRequest
{
	FNephStateChangeRequest() = default;
	FNephStateChangeRequest(FGameplayTag reqState) : NewState(reqState) { }
	
	FGameplayTag NewState = FGameplayTag::EmptyTag;
};

USTRUCT()
struct NEPHGLITTERTACTICS_API FNephBattleControllerEvents
{
	GENERATED_BODY()

public:

	FGameplayTag OnBattleStateChanged;
	FGameplayTag OnBattleStateEnded;

	TArray<FNephStateChangeRequest> StateChangeRequests;
};
