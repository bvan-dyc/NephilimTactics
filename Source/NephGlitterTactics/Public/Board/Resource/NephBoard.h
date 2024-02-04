#pragma once

#include "Board/NephTileData.h"

#include "CoreMinimal.h"

struct NEPHGLITTERTACTICS_API FNephBoard
{
	FIntPoint GetCellCoordinatesAtLocation(const FVector& Location) const;
	int32 GetCellIndex(int32 x, int32 y) const;
	int32 GetCellIndexFromPoint(const FIntPoint& Point) const;
	FNephTileData* GetTileWithCoordinates(const FIntPoint& Point);

	const FNephTileData* GetCellAtLocationClamped(const FVector& Location) const;
	const FNephTileData* FindCellAtLocation(const FVector& Location) const;
	FVector GetTileWorldLocation(int32 X, int32 Y) const;
	FVector GetTileWorldLocationFromPoint(const FIntPoint& Point) const;
	
	TArray<struct FNephTileData> Board;
	
	FVector2D BoardCenterLocation = FVector2D(0, 0);

	float TileSize = 250.0f;

	int32 TileCountX = 0;
	int32 TileCountY = 0;

	int32 GridSizeX = 20;
	int32 GridSizeY = 20;

	TWeakObjectPtr<class ANepGrid> GridActor;
};
