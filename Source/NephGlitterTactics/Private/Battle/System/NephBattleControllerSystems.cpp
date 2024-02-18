#include "Battle/System/NephBattleControllerSystems.h"

#include "Battle/Resource/NephBattleControllerEvents.h"

void FNephBattleControllerSystems::ClearEvents(FArcRes<FNephBattleControllerEvents> Events)
{
	*Events = FNephBattleControllerEvents();
}
