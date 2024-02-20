#include "Board/NephBoardSetup.h"

#include "ArcScheduleBuilder.h"
#include "ArcUniverse.h"
#include "Board/Resource/NephBoardEvents.h"
#include "Board/System/NephBoardSystems.h"

void FNephBoardSetup::Setup(FArcUniverse& Universe, FArcScheduleBuilder& InitScheduleBuilder, FArcScheduleBuilder& TickScheduleBuilder)
{
	Universe.AddResource(FNephBoardEvents());
	Universe.AddResource(FNephBoard());
	Universe.AddResource(FNephLevelGlobals());

	InitScheduleBuilder
		.AddSystem(&FNephBoardSystems::InitializeGlobals)
		.AddSystemSeq(&FNephBoardSystems::InitBoardUI);
	
	TickScheduleBuilder
		.AddSystem(&FNephBoardSystems::HandleBoardCreatedEvent)
		.AddSystemSeq(&FNephBoardSystems::HandleHoverOverTileCommands)
		.AddSystemSeq(&FNephBoardSystems::UpdateHoveredTile)
		.AddSystemToStage(TEXT("Nephilim_EventCleanUpStage"), &FNephBoardSystems::ClearEvents);
}

void FNephBoardSetup::SetupForEditor(FArcUniverse& Universe, FArcScheduleBuilder& InitScheduleBuilder, FArcScheduleBuilder& TickScheduleBuilder)
{
	Universe.AddResource(FNephBoardEvents());
	Universe.AddResource(FNephBoard());
	Universe.AddResource(FNephLevelGlobals());

	InitScheduleBuilder
		.AddSystem(&FNephBoardSystems::InitializeGlobals);
	
	TickScheduleBuilder
		.AddSystem(&FNephBoardSystems::HandleBoardCreatedEvent)
		.AddSystemToStage(TEXT("Nephilim_EventCleanUpStage"), &FNephBoardSystems::ClearEvents);
}
