#include "Units/NephUnitsSetup.h"

#include "ArcScheduleBuilder.h"
#include "ArcUniverse.h"
#include "Units/Resource/NephUnitsEvents.h"
#include "Units/System/NephUnitsSystems.h"

void FNepUnitsSetup::Setup(FArcUniverse& Universe, FArcScheduleBuilder& InitScheduleBuilder, FArcScheduleBuilder& TickScheduleBuilder)
{
	Universe.AddResource(FNephUnitsEvents());
	
	TickScheduleBuilder
		.AddSystem(FNephUnitsSystems::SnapUnitsToBoard)
		.AddSystemToStage(TEXT("Nephilim_EventCleanUpStage"), &FNephUnitsSystems::ClearEvents);
}

void FNepUnitsSetup::SetupForEditor(FArcUniverse& Universe, FArcScheduleBuilder& InitScheduleBuilder, FArcScheduleBuilder& TickScheduleBuilder)
{
	Universe.AddResource(FNephUnitsEvents());
	
	TickScheduleBuilder
		.AddSystem(FNephUnitsSystems::SnapUnitsToBoard)
		.AddSystemToStage(TEXT("Nephilim_EventCleanUpStage"), &FNephUnitsSystems::ClearEvents);
}
