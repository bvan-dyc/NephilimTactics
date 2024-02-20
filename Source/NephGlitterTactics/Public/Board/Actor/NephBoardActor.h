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

	UPROPERTY(VisibleAnywhere)
	TArray<struct FNephTileData> BoardTiles;

	UPROPERTY(VisibleAnywhere)
	float TileSize = 250.0f;

	UPROPERTY(EditAnywhere)
	int32 GridSizeX = 20;
	UPROPERTY(EditAnywhere)
	int32 GridSizeY = 20;

private:

	virtual void BeginPlay() override;
	
	void SetupCollisionPlane() const;
	
	UFUNCTION(CallInEditor)
	void GenerateBoard();
	
	UFUNCTION(CallInEditor)
	void DrawBoard() const;

	int32 GetTileIndex(int32 x, int32 y) const { return x + (y * GridSizeX); };

	FIntPoint GetTileCoordinatesAtLocation(const FVector& location) const;
	void GetDataFromTileActor();
	class ANephTileActor* SpawnTileAtLocation(const FVector& Location);

	const struct FNephTileData&	GetTileAtLocationClamped(const FVector& location) const;
	const struct FNephTileData*	FindTileAtLocation(const FVector& location) const;
	FVector GetTileLocation(int32 x, int32 y) const;
	
	FVector BoardCenterLocation = FVector::ZeroVector;

	UPROPERTY(EditAnywhere)
	TSubclassOf<ANephTileActor> DefaultTileClass;

	UPROPERTY()
	TObjectPtr<UStaticMeshComponent> CollisionPlane;

	bool bShowCollisionPlane = false;
};
