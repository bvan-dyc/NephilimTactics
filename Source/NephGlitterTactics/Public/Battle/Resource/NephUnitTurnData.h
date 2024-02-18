#pragma once

#include "CoreMinimal.h"
#include "ArcEntityHandleInternal.h"
#include "Board/NephBoardUtils.h"

#include "NephUnitTurnData.generated.h"

USTRUCT()
struct FNephUnitTurnData
{
	GENERATED_BODY()
    
public:

	~FNephUnitTurnData() {}

	FArcEntityHandle UnitHandle;
	bool bHasUnitMoved = false;
	bool bHasUnitActed = false;
	FIntPoint StartTile = FIntPoint::ZeroValue;
	ENephDirections StartDirection;
};