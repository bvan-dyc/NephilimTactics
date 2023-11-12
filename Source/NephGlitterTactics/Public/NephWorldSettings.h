#pragma once

#include "FlowWorldSettings.h"
#include "GameFramework/WorldSettings.h"

#include "NephWorldSettings.generated.h"

UCLASS()
class NEPHGLITTERTACTICS_API ANephWorldSettings : public AFlowWorldSettings
{
	GENERATED_BODY()

public:

	ANephWorldSettings(const FObjectInitializer& ObjectInitializer);
};
