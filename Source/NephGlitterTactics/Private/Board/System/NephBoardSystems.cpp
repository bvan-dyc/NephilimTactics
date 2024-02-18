#include "Board/System/NephBoardSystems.h"

#include "Board/Resource/NephBoard.h"
#include "Board/NephTileData.h"
#include "Board/Actor/NephBoardActor.h"
#include "Board/Resource/NephBoardEvents.h"
#include "Resource/ArcCoreData.h"

void FNephBoardSystems::HandleBoardCreatedEvent(FArcRes<FArcCoreData> CoreData, FArcRes<FNephBoard> Board, FArcRes<FNephBoardEvents> BoardEvents)
{
	if (BoardEvents->BoardCreatedEvents.Num() < 1) { return; }
	
	
}

void FNephBoardSystems::GenerateBoard(const UWorld* World, const FArcRes<FNephBoard>& Board)
{
	if (!World) { return; }
	
	const FVector& Center = FVector::ZeroVector;
	Board->BoardCenterLocation = FVector2D::ZeroVector;
	
	Board->TileCountX = 20;
	Board->TileCountY = 20;

	Board->Board.AddZeroed(Board->TileCountX * Board->TileCountY);
	for (int32 x = 0; x < Board->TileCountX; ++x)
	{
		for (int32 y = 0; y < Board->TileCountY; ++y)
		{
			const int32 index = x + (y * Board->TileCountX);
			
			FNephTileData* NephTileData = &Board->Board[index];
			NephTileData->TileCoordinates.X = x;
			NephTileData->TileCoordinates.Y = y;
		}
	}
	
	DrawBoard(World, Board);
}

void FNephBoardSystems::DrawBoard(const UWorld* World, const FArcRes<FNephBoard>& Board)
{
	const FVector cellExtent = FVector(Board->TileSize / 2.f, Board->TileSize / 2.f, 0.f);

	const float gridHeight = 0;
	for (int32 x = 0; x < Board->TileCountX; ++x)
	{
		for (int32 y = 0; y < Board->TileCountY; ++y)
		{
			FColor cellColor = FColor::Yellow;

			FVector cellLocation = Board->GetTileWorldLocationFromPoint(FIntPoint(x, y));
			cellLocation.Z = gridHeight;
			DrawDebugBox(World, cellLocation, cellExtent, FQuat::Identity, cellColor, false, 60.f);
		}
	}
}

void FNephBoardSystems::ClearEvents(FArcRes<FNephBoardEvents> Events)
{
	*Events = FNephBoardEvents();
}
