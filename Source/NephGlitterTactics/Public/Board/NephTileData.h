#pragma once

#include "CoreMinimal.h"
#include "ArcEntityHandleInternal.h"
#include "NephTileData.generated.h"

USTRUCT()
struct NEPHGLITTERTACTICS_API FNephTileData
{

public:

	GENERATED_BODY()
	
	FNephTileData() {}
	FNephTileData(int32 X, int32 Y) : TileCoordinates(FIntPoint(X, Y)) { }
	
	int32 TileHeight = 0;

	UPROPERTY(VisibleAnywhere)
	FIntPoint TileCoordinates = FIntPoint(0, 0);

	FArcEntityHandle TileContent;

	//Pathfinding
	TOptional<FIntPoint> PrevCoordinates;
	int32 Distance = 0;

	TWeakObjectPtr<class ANephTileActor> TileActor;
};
