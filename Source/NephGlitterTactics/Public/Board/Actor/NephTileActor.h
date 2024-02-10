#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Volume.h"

#include "NephTileActor.generated.h"

UCLASS(Blueprintable)
class ANephTileActor : public AActor
{
	GENERATED_BODY()

public:
	
	ANephTileActor();

	class UStaticMesh* GetHexMesh() const { return TileMeshComponent ? TileMeshComponent->GetStaticMesh() : nullptr; }

private:

	UPROPERTY(EditAnywhere)
	TObjectPtr<UStaticMesh> HexMesh;
	
	UPROPERTY(EditAnywhere)
	TObjectPtr<class UStaticMeshComponent> TileMeshComponent;
};
