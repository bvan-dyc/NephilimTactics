#include "Core/NephECSSetup.h"

#include "ArcScheduleBuilder.h"
#include "Board/NephBoardSetup.h"

void UNephECSSetup::SetupECSForGame(FArcUniverse& Universe, UWorld& World, FArcScheduleBuilder& InitScheduleBuilder, FArcScheduleBuilder& TickScheduleBuilder)
{
	TickScheduleBuilder
		.AddUnrealStages()
		.AddStageAfter(TEXT("Nephilim_EventCleanUpStage"), FArcScheduleStage::LastDemotableStage);
	
	FNephBoardSetup::Setup(Universe, InitScheduleBuilder, TickScheduleBuilder);
}

void UNephECSSetup::SetupECSForServer(FArcUniverse& Universe, UWorld& World, FArcScheduleBuilder& InitScheduleBuilder, FArcScheduleBuilder& TickScheduleBuilder)
{
	TickScheduleBuilder
		.AddUnrealStages()
		.AddStageAfter(TEXT("Nephilim_EventCleanUpStage"), FArcScheduleStage::LastDemotableStage);

	FNephBoardSetup::Setup(Universe, InitScheduleBuilder, TickScheduleBuilder);
}

void UNephECSSetup::SetupECSForEditor(FArcUniverse& Universe, UWorld& World, FArcScheduleBuilder& InitScheduleBuilder, FArcScheduleBuilder& TickScheduleBuilder)
{
	TickScheduleBuilder
		.AddStageAfter(TEXT("Nephilim_EventCleanUpStage"), FArcScheduleStage::DefaultStage);

	FNephBoardSetup::SetupForEditor(Universe, InitScheduleBuilder, TickScheduleBuilder);
}
