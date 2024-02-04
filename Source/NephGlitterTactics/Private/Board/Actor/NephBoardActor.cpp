#include "Board/Actor/NephBoardActor.h"

#include "NephWorldSettings.h"
#include "Board/NephTileData.h"

ANephBoardActor::ANephBoardActor()
{
	
}

void ANephBoardActor::GenerateBoard()
{
	const UWorld* World = GetWorld();
	if (!World) { return; }
	
	const FVector& Center = GetActorLocation();
	BoardCenterLocation = Center;
	
	TileCountX = GridSizeX;
	TileCountY = GridSizeY;

	const float startTileX = (Center.X - ((TileCountX / 2) * TileSize));
	const float startTileY = (Center.Y - ((TileCountY / 2) * TileSize));

	FCollisionQueryParams traceParams;
	traceParams.bTraceComplex = false;
	traceParams.MobilityType = EQueryMobilityType::Static;
	
	BoardGrid.AddZeroed(TileCountX * TileCountY);
	for (int32 x = 0; x < TileCountX; ++x)
	{
		const float TileLocationX = startTileX + (x * TileSize) + (TileSize / 2.f);

		for (int32 y = 0; y < TileCountY; ++y)
		{
			const float TileLocationY = startTileY + (y * TileSize) + (TileSize / 2.f);

			const int32 index = x + (y * TileCountX);
			BoardGrid[index] = FNephTileData(x, y);
		}
	}
	
	DrawBoard();
}

void ANephBoardActor::DrawBoard() const
{
	const UWorld* World = GetWorld();
	const ANephWorldSettings* worldSettings = World ? Cast<ANephWorldSettings>(World->GetWorldSettings()) : nullptr;
	if (!worldSettings) { return; }

	const FVector cellExtent = FVector(TileSize / 2.f, TileSize / 2.f, 0.f);

	//const FBoxSphereBounds& bounds = GetBounds();
	const float gridHeight = GetActorLocation().Z;//bounds.BoxExtent.Z;

	for (int32 x = 0; x < TileCountX; ++x)
	{
		for (int32 y = 0; y < TileCountY; ++y)
		{
			FColor cellColor = FColor::Yellow;

			FVector cellLocation = GetCellLocation(x, y);
			cellLocation.Z = gridHeight;
			DrawDebugBox(World, cellLocation, cellExtent, FQuat::Identity, cellColor, false, 60.f);
		}
	}
}

const FNephTileData& ANephBoardActor::GetCellAtLocationClamped(const FVector& location) const
{
	const float startCellX = (BoardCenterLocation.X - ((TileCountX / 2) * TileSize));
	const float startCellY = (BoardCenterLocation.Y - ((TileCountY / 2) * TileSize));
	const int32 cellX = FMath::Clamp(FMath::FloorToInt((location.X - startCellX) / TileSize), 0, TileCountX - 1);
	const int32 cellY = FMath::Clamp(FMath::FloorToInt((location.Y - startCellY) / TileSize), 0, TileCountY - 1);
	const int32 index = (cellX + (cellY * TileCountX));
	return BoardGrid[index];
}

const FNephTileData* ANephBoardActor::FindCellAtLocation(const FVector& location) const
{
	const FIntPoint coords = GetCellCoordinatesAtLocation(location);
	const int32 index = GetCellIndex(coords.X, coords.Y);
	return BoardGrid.IsValidIndex(index) ? &BoardGrid[index] : nullptr;
}

FVector ANephBoardActor::GetCellLocation(int32 x, int32 y) const
{
	const float cellExtent = TileSize / 2.f;
	return FVector((x * TileSize) + cellExtent, (y * TileSize) + cellExtent, 0.f) + 
		FVector(BoardCenterLocation.X, BoardCenterLocation.Y, 0.f) - 
		FVector(TileCountX * cellExtent, TileCountY * cellExtent, 0.f);
}

FIntPoint ANephBoardActor::GetCellCoordinatesAtLocation(const FVector& location) const
{
	if (!ensure(TileSize > 0)) { return FIntPoint(INDEX_NONE, INDEX_NONE); }

	const float startCellX = (BoardCenterLocation.X - ((TileCountX / 2) * TileSize));
	const float startCellY = (BoardCenterLocation.Y - ((TileCountY / 2) * TileSize));
	const int32 cellX = FMath::FloorToInt((location.X - startCellX) / TileSize);
	const int32 cellY = FMath::FloorToInt((location.Y - startCellY) / TileSize);

	return FIntPoint(cellX, cellY);
}
