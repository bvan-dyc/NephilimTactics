#include "Board/Resource/NephBoard.h"
#include "Board/NephTileData.h"
#include "Board/Actor/NephBoardActor.h"

int32 FNephBoard::GetTileIndexFromPoint(const FIntPoint& Point) const
{
	if (Point.X < 0 || Point.Y < 0 || Point.X >= TileCountX || Point.Y >= TileCountY) { return INDEX_NONE; }
	return (Point.X + (Point.Y * TileCountX));
}

FNephTileData* FNephBoard::GetTileWithCoordinates(const FIntPoint& Point)
{
	for (FNephTileData& Tile : BoardTiles)
	{
		if (Tile.TileCoordinates == Point)
		{
			return &Tile;
		}
	}
	return nullptr;
}

const FNephTileData* FNephBoard::GetTileAtLocationClamped(const FVector& Location) const
{
	const float startTileX = (BoardCenterLocation.X - ((TileCountX / 2) * TileSize));
	const float startTileY = (BoardCenterLocation.Y - ((TileCountY / 2) * TileSize));
	const int32 tileX = FMath::Clamp(FMath::FloorToInt((Location.X - startTileX) / TileSize), 0, TileCountX - 1);
	const int32 tileY = FMath::Clamp(FMath::FloorToInt((Location.Y - startTileY) / TileSize), 0, TileCountY - 1);
	const int32 index = (tileX + (tileY * TileCountX));
	
	if (!BoardTiles.IsValidIndex(index)) { return nullptr; }
	
	return &BoardTiles[index];
}

FNephTileData* FNephBoard::FindTileAtLocation(const FVector& Location)
{
	const FIntPoint coords = GetTileCoordinatesAtLocation(Location);
	const int32 index = GetTileIndexFromPoint(FIntPoint(coords.X, coords.Y));
	
	if (!BoardTiles.IsValidIndex(index)) { return nullptr; }
	
	return &BoardTiles[index];
}

FVector FNephBoard::GetLocationAtTileCoordinates(FIntPoint Coordinates) const
{
	const float tileExtent = TileSize / 2.f;
	return FVector((Coordinates.X * TileSize) + tileExtent, (Coordinates.Y * TileSize) + tileExtent, 0.f) + 
		FVector(BoardCenterLocation.X, BoardCenterLocation.Y, 0.f) - 
		FVector(TileCountX * tileExtent, TileCountY * tileExtent, 0.f);
}

FVector FNephBoard::GetTileWorldLocationFromPoint(const FIntPoint& Point) const
{
	const float tileExtent = TileSize / 2.f;
	return FVector((Point.X * TileSize) + tileExtent, (Point.Y * TileSize) + tileExtent, 0.f) + 
        FVector(BoardCenterLocation.X, BoardCenterLocation.Y, 0.f) - 
        FVector(TileCountX * tileExtent, TileCountY * tileExtent, 0.f);
}

void FNephBoard::InitFromActor(const ANephBoardActor* Actor)
{
	if (!Actor) { return; }

	BoardTiles.Reset();
		
	TileSize = BoardActor->TileSize;
	TileCountX = BoardActor->GridSizeX;
	TileCountY = BoardActor->GridSizeY;
	BoardTiles = Actor->BoardTiles;
}

FIntPoint FNephBoard::GetTileCoordinatesAtLocation(const FVector& Location) const
{
	if (!ensure(TileSize > 0)) { return FIntPoint(INDEX_NONE, INDEX_NONE); }

	const float startTileX = (BoardCenterLocation.X - ((TileCountX / 2) * TileSize));
	const float startTileY = (BoardCenterLocation.Y - ((TileCountY / 2) * TileSize));
	const int32 tileX = FMath::FloorToInt((Location.X - startTileX) / TileSize);
	const int32 tileY = FMath::FloorToInt((Location.Y - startTileY) / TileSize);

	return FIntPoint(tileX, tileY);
}
