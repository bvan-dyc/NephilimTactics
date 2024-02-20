#pragma once

#include "ArcRes.h"
#include "Board/Resource/NephBoard.h"
#include "Board/Resource/NephBoardEvents.h"
#include "Board/Resource/NephLevelGlobals.h"
#include "Resource/ArcCoreData.h"

struct FNephBoardSystems
{
	// Init
	static void InitializeGlobals(FArcRes<FArcCoreData> CoreData, FArcRes<FNephLevelGlobals> LevelGlobals);
	static void InitBoardUI(FArcRes<FArcCoreData> CoreData, FArcRes<FNephBoard> Board, const FArcRes<FNephLevelGlobals> LevelGlobals);
	
	//Tick
	static void HandleBoardCreatedEvent(FArcRes<FArcCoreData> CoreData, FArcRes<FNephBoard> Board, FArcRes<FNephBoardEvents> BoardEvents, FArcRes<
	                                    FNephLevelGlobals> LevelGlobals);
	static void HandleHoverOverTileCommands(FArcRes<FArcCoreData> CoreData, FArcRes<FNephBoard> Board, FArcRes<FNephBoardEvents> BoardEvents);
	static void UpdateHoveredTile(FArcRes<FArcCoreData> CoreData, FArcRes<FNephBoard> Board);
	static void ClearEvents(FArcRes<FNephBoardEvents> Events);

private:
	static void GenerateBoard(const UWorld* World, FArcRes<FNephBoard>& Board, const FArcRes<FNephLevelGlobals> LevelGlobals);
};
