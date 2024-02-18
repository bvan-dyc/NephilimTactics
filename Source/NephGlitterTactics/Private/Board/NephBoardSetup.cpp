#include "Board/NephBoardSetup.h"

#include "ArcScheduleBuilder.h"
#include "ArcUniverse.h"
#include "Board/Resource/NephBoardEvents.h"
#include "Board/System/NephBoardSystems.h"

void FNephBoardSetup::Setup(FArcUniverse& Universe, FArcScheduleBuilder& InitScheduleBuilder, FArcScheduleBuilder& TickScheduleBuilder)
{
	Universe.AddResource(FNephBoardEvents());
	Universe.AddResource(FNephBoard());
	
	InitScheduleBuilder
		.AddSystem(&FNephBoardSystems::BuildBoard);
	
	TickScheduleBuilder
		.AddSystemToStage(TEXT("Nephilim_EventCleanUpStage"), &FNephBoardSystems::ClearEvents);
}

void FNephBoardSetup::SetupForEditor(FArcUniverse& Universe, FArcScheduleBuilder& InitScheduleBuilder, FArcScheduleBuilder& TickScheduleBuilder)
{
	Universe.AddResource(FNephBoardEvents());
	Universe.AddResource(FNephBoard());
	
	InitScheduleBuilder
		.AddSystem(&FNephBoardSystems::BuildBoard);
	
	TickScheduleBuilder
		.AddSystemToStage(TEXT("Nephilim_EventCleanUpStage"), &FNephBoardSystems::ClearEvents);
}
