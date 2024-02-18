#pragma once

#include "CoreMinimal.h"
#include "ArcEntityHandleInternal.h"

struct NEPHGLITTERTACTICS_API FNephTileData
{

public:

	FNephTileData() {}
	FNephTileData(int32 X, int32 Y) : TileCoordinates(FIntPoint(X, Y)) { }
	
	int32 TileHeight = 0;

	FIntPoint TileCoordinates = FIntPoint(0, 0);

	FArcEntityHandle TileContent;

	//Pathfinding
	TOptional<FIntPoint> PrevCoordinates;
	int32 Distance = 0;
};
