#include "Board/System/NephBoardSystems.h"

#include "Board/Resource/NephBoard.h"
#include "Board/NephTileData.h"
#include "Board/Resource/NephBoardEvents.h"
#include "Resource/ArcCoreData.h"

void FNephBoardSystems::BuildBoard(FArcRes<FArcCoreData> CoreData, FArcRes<FNephBoard> Board)
{
	const UWorld* World = CoreData->World.Get();
	if (!World) { return; }

	GenerateBoard(World, Board);
}

void FNephBoardSystems::GenerateBoard(const UWorld* World, const FArcRes<FNephBoard>& Board)
{
	if (!World) { return; }
	
	const FVector& Center = FVector::ZeroVector;
	Board->BoardCenterLocation = FVector2D::ZeroVector;
	
	Board->TileCountX = 20;
	Board->TileCountY = 20;

	const float startTileX = (Center.X - ((Board->TileCountX / 2) * Board->TileSize));
	const float startTileY = (Center.Y - ((Board->TileCountY / 2) * Board->TileSize));

	Board->Board.AddZeroed(Board->TileCountX * Board->TileCountY);
	for (int32 x = 0; x < Board->TileCountX; ++x)
	{
		const float TileLocationX = startTileX + (x * Board->TileSize) + (Board->TileSize / 2.f);

		for (int32 y = 0; y < Board->TileCountY; ++y)
		{
			const float TileLocationY = startTileY + (y * Board->TileSize) + (Board->TileSize / 2.f);

			const int32 index = x + (y * Board->TileCountX);
			
			FNephTileData* NephTileData = &Board->Board[index];
			NephTileData->Coordinates.X = x;
			NephTileData->Coordinates.Y = y;
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