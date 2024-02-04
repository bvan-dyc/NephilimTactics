#pragma once

#include "ArcRes.h"
#include "Board/Resource/NephBoard.h"
#include "Board/Resource/NephBoardEvents.h"
#include "Resource/ArcCoreData.h"

struct FNephBoardSystems
{
	// Init
	static void BuildBoard(FArcRes<FArcCoreData> CoreData, FArcRes<FNephBoard> Board);
	static void GenerateBoard(const UWorld* World, const FArcRes<FNephBoard>& Board);
	static void DrawBoard(const UWorld* World, const FArcRes<FNephBoard>& Board);
	static void ClearEvents(FArcRes<FNephBoardEvents> Events);
};
