#pragma once

#include "ArcRes.h"
#include "Board/Resource/NephBoard.h"

struct FNephUnitsSystems
{
	static void SnapUnitsToBoard(FArcRes<FNephBoard> Board, FArcRes<struct FNephUnitsEvents> UnitEvents);
	static void HandlePlaceEntityOnTileCommands(const FArcUniverse& Universe, FArcRes<struct FNephUnitsEvents> Events, FArcRes<FNephBoard> Board);
	static void ClearEvents(FArcRes<struct FNephUnitsEvents> Events);
};
