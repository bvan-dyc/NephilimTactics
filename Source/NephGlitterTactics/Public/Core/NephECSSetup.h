#pragma once

#include "CoreMinimal.h"
#include "ArcECSSetup.h"
#include "NephECSSetup.generated.h"

UCLASS()
class NEPHGLITTERTACTICS_API UNephECSSetup : public UArcECSSetup
{
	GENERATED_BODY()

public:

	virtual void SetupECSForGame(FArcUniverse& Universe, UWorld& World, FArcScheduleBuilder& InitScheduleBuilder, FArcScheduleBuilder& TickScheduleBuilder) override;
	virtual void SetupECSForServer(FArcUniverse& Universe, UWorld& World, FArcScheduleBuilder& InitScheduleBuilder, FArcScheduleBuilder& TickScheduleBuilder) override;
	virtual void SetupECSForEditor(FArcUniverse& Universe, UWorld& World, FArcScheduleBuilder& InitScheduleBuilder, FArcScheduleBuilder& TickScheduleBuilder) override;
};
