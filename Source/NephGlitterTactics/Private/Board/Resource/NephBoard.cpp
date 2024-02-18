#include "Board/Resource/NephBoard.h"
#include "Board/NephTileData.h"

int32 FNephBoard::GetCellIndex(int32 x, int32 y) const
{
	if (x < 0 || y < 0 || x >= TileCountX || y >= TileCountY) { return INDEX_NONE; }
	return (x + (y * TileCountX));
}

int32 FNephBoard::GetCellIndexFromPoint(const FIntPoint& Point) const
{
	if (Point.X < 0 || Point.Y < 0 || Point.X >= TileCountX || Point.Y >= TileCountY) { return INDEX_NONE; }
	return (Point.X + (Point.Y * TileCountX));
}

FNephTileData* FNephBoard::GetTileWithCoordinates(const FIntPoint& Point)
{
	for (FNephTileData& Tile : Board)
	{
		if (Tile.TileCoordinates == Point)
		{
			return &Tile;
		}
	}
	return nullptr;
}

const FNephTileData* FNephBoard::GetCellAtLocationClamped(const FVector& Location) const
{
	const float startCellX = (BoardCenterLocation.X - ((TileCountX / 2) * TileSize));
	const float startCellY = (BoardCenterLocation.Y - ((TileCountY / 2) * TileSize));
	const int32 cellX = FMath::Clamp(FMath::FloorToInt((Location.X - startCellX) / TileSize), 0, TileCountX - 1);
	const int32 cellY = FMath::Clamp(FMath::FloorToInt((Location.Y - startCellY) / TileSize), 0, TileCountY - 1);
	const int32 index = (cellX + (cellY * TileCountX));
	
	if (!Board.IsValidIndex(index)) { return nullptr; }
	
	return &Board[index];
}

const FNephTileData* FNephBoard::FindCellAtLocation(const FVector& Location) const
{
	const FIntPoint coords = GetCellCoordinatesAtLocation(Location);
	const int32 index = GetCellIndex(coords.X, coords.Y);
	
	if (!Board.IsValidIndex(index)) { return nullptr; }
	
	return &Board[index];
}

FVector FNephBoard::GetTileWorldLocation(int32 X, int32 Y) const
{
	const float cellExtent = TileSize / 2.f;
	return FVector((X * TileSize) + cellExtent, (Y * TileSize) + cellExtent, 0.f) + 
        FVector(BoardCenterLocation.X, BoardCenterLocation.Y, 0.f) - 
        FVector(TileCountX * cellExtent, TileCountY * cellExtent, 0.f);
}

FVector FNephBoard::GetLocationAtTileCoordinates(FIntPoint Coordinates) const
{
	const float cellExtent = TileSize / 2.f;
	return FVector((Coordinates.X * TileSize) + cellExtent, (Coordinates.Y * TileSize) + cellExtent, 0.f) + 
		FVector(BoardCenterLocation.X, BoardCenterLocation.Y, 0.f) - 
		FVector(TileCountX * cellExtent, TileCountY * cellExtent, 0.f);
}

FVector FNephBoard::GetTileWorldLocationFromPoint(const FIntPoint& Point) const
{
	const float cellExtent = TileSize / 2.f;
	return FVector((Point.X * TileSize) + cellExtent, (Point.Y * TileSize) + cellExtent, 0.f) + 
        FVector(BoardCenterLocation.X, BoardCenterLocation.Y, 0.f) - 
        FVector(TileCountX * cellExtent, TileCountY * cellExtent, 0.f);
}

FIntPoint FNephBoard::GetCellCoordinatesAtLocation(const FVector& Location) const
{
	if (!ensure(TileSize > 0)) { return FIntPoint(INDEX_NONE, INDEX_NONE); }

	const float startCellX = (BoardCenterLocation.X - ((TileCountX / 2) * TileSize));
	const float startCellY = (BoardCenterLocation.Y - ((TileCountY / 2) * TileSize));
	const int32 cellX = FMath::FloorToInt((Location.X - startCellX) / TileSize);
	const int32 cellY = FMath::FloorToInt((Location.Y - startCellY) / TileSize);

	return FIntPoint(cellX, cellY);
}
