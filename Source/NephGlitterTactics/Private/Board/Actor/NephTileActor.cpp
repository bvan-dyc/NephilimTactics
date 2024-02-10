#include "Board/Actor/NephTileActor.h"

ANephTileActor::ANephTileActor()
{
	PrimaryActorTick.bCanEverTick = false;

	TileMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("TileMesh"));
	TileMeshComponent->SetupAttachment(GetRootComponent());
	TileMeshComponent->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
	TileMeshComponent->SetCollisionResponseToAllChannels(ECR_Block);
	TileMeshComponent->SetStaticMesh(HexMesh);
}
