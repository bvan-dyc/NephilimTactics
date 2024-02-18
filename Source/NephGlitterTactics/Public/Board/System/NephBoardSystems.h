#pragma once

#include "ArcECSSubsystem.h"
#include "ArcRes.h"
#include "Board/Resource/NephBoard.h"
#include "Board/Resource/NephBoardEvents.h"
#include "Resource/ArcCoreData.h"

struct FNephBoardSystems
{
	// Init
	static void ClearEvents(FArcRes<FNephBoardEvents> Events);

private:
	void HandleBoardCreatedEvent(FArcRes<FArcCoreData> CoreData, FArcRes<FNephBoard> Board,
	                             FArcRes<FNephBoardEvents> BoardEvents);
	void GenerateBoard(const UWorld* World, const FArcRes<FNephBoard>& Board);
	void DrawBoard(const UWorld* World, const FArcRes<FNephBoard>& Board);
};
