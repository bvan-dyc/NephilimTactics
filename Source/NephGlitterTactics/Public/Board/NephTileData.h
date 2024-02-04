#pragma once

#include "CoreMinimal.h"

struct NEPHGLITTERTACTICS_API FNephTileData
{

public:

	FNephTileData() {}
	FNephTileData(int32 X, int32 Y) : Coordinates(FIntPoint(X, Y)) { }
	
	int32 Height = 0;

	FIntPoint Coordinates = FIntPoint(0, 0);
	FIntPoint WorldLocation = FIntPoint(0, 0);
};
