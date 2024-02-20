#pragma once

#include "Board/NephTileData.h"

#include "CoreMinimal.h"

struct NEPHGLITTERTACTICS_API FNephBoard
{
public:
	
	TArray<struct FNephTileData> BoardTiles;
	
	FVector2D BoardCenterLocation = FVector2D(0, 0);

	float TileSize = 250.0f;

	int32 TileCountX = 20;
	int32 TileCountY = 20;

	TWeakObjectPtr<class ANephBoardActor> BoardActor;
	TWeakObjectPtr<class AActor> TileSelectorActor;

	FIntPoint SelectedTile = FIntPoint::ZeroValue;
	
public:
	
	// Utils
	FIntPoint GetTileCoordinatesAtLocation(const FVector& Location) const;
	int32 GetTileIndexFromPoint(const FIntPoint& Point) const;
	FNephTileData* GetTileWithCoordinates(const FIntPoint& Point);

	const FNephTileData* GetTileAtLocationClamped(const FVector& Location) const;
	FNephTileData* FindTileAtLocation(const FVector& Location);
	FVector GetLocationAtTileCoordinates(FIntPoint Coordinates) const;
	
	FVector GetTileWorldLocationFromPoint(const FIntPoint& Point) const;
	
	FVector GetTileSnapLocation(FIntPoint Coordinates) const { return GetLocationAtTileCoordinates(Coordinates); }
	void InitFromActor(const ANephBoardActor* BoardActor);
};
