#include "Narrative/NephNarrativeSetup.h"
#include "ArcUniverse.h"
#include "Narrative/Resource/NephNarrativeEvents.h"

void FNephNarrativeSetup::Setup(FArcUniverse& Universe, FArcScheduleBuilder& InitScheduleBuilder, FArcScheduleBuilder& TickScheduleBuilder)
{
	Universe.AddResource(FNephNarrativeEvents());
}
