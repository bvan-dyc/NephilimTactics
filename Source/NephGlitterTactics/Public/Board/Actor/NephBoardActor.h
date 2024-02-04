#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Volume.h"
#include "Board/NephTileData.h"
#include "NephBoardActor.generated.h"

UCLASS(Blueprintable)
class ANephBoardActor : public AActor
{
	GENERATED_BODY()

public:
	
	ANephBoardActor();
	
private:

	UFUNCTION(CallInEditor)
	void GenerateBoard();
	
	UFUNCTION(CallInEditor)
	void DrawBoard() const;

	int32 GetCellIndex(int32 x, int32 y) const { return x + (y * TileCountX); };

	FIntPoint GetCellCoordinatesAtLocation(const FVector& location) const;
	
	const struct FNephTileData&	GetCellAtLocationClamped(const FVector& location) const;
	const struct FNephTileData*	FindCellAtLocation(const FVector& location) const;
	FVector GetCellLocation(int32 x, int32 y) const;

protected:
	
	UPROPERTY(EditAnywhere, Category="Board", Meta = (ClampMin = "1"))
	float TileSize = 250.0f;

	int32 TileCountX = 0;
	int32 TileCountY = 0;

	int32 GridSizeX = 20;
	int32 GridSizeY = 20;

	TArray<FNephTileData> BoardGrid;

	FVector BoardCenterLocation = FVector::ZeroVector;
};
