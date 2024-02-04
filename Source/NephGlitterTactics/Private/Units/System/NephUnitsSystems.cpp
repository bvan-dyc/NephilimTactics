#include "Units/System/NephUnitsSystems.h"

#include "Units/Resource/NephUnitsEvents.h"

void FNephUnitsSystems::ClearEvents(FArcRes<FNephUnitsEvents> Events)
{
	*Events = FNephUnitsEvents();
}
