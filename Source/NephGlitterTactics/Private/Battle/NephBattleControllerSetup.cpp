#include "Battle/NephBattleControllerSetup.h"

#include "ArcScheduleBuilder.h"
#include "ArcUniverse.h"
#include "Battle/Resource/NephBattleController.h"
#include "Battle/Resource/NephBattleControllerEvents.h"
#include "Battle/System/NephBattleControllerSystems.h"

void FNephBattleControllerSetup::Setup(FArcUniverse& Universe, FArcScheduleBuilder& InitScheduleBuilder, FArcScheduleBuilder& TickScheduleBuilder)
{
	Universe.AddResource(FNephBattleControllerEvents());
	Universe.AddResource(FNephBattleController());
	
	TickScheduleBuilder
		.AddSystemToStage(TEXT("Nephilim_EventCleanUpStage"), &FNephBattleControllerSystems::ClearEvents);
}
