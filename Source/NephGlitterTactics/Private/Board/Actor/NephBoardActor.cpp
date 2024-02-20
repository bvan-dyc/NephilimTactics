#include "Board/Actor/NephBoardActor.h"

#include "ArcECSSubsystem.h"
#include "NephWorldSettings.h"
#include "Board/NephTileData.h"
#include "Board/Actor/NephTileActor.h"
#include "Board/Resource/NephBoardEvents.h"

ANephBoardActor::ANephBoardActor()
{
	PrimaryActorTick.bCanEverTick = false;

	USceneComponent* SceneComponent = CreateDefaultSubobject<USceneComponent>(TEXT("SceneComponent"));
	RootComponent = SceneComponent;
	SetRootComponent(RootComponent);
	
	CollisionPlane = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("CollisionPlane"));
	CollisionPlane->SetupAttachment(GetRootComponent());
	CollisionPlane->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
	CollisionPlane->SetCollisionResponseToAllChannels(ECR_Block);

	UArcECSSubsystem* CoreSubsystem = UWorld::GetSubsystem<UArcECSSubsystem>(GetWorld());
	FArcUniverse* Universe = CoreSubsystem ? &CoreSubsystem->GetUniverse() : nullptr;
	if (FNephBoardEvents* BoardEvents = Universe ? Universe->GetResource<FNephBoardEvents>() : nullptr)
	{
		BoardEvents->BoardCreatedEvents.Emplace(this);
	}
}

void ANephBoardActor::BeginPlay()
{
	Super::BeginPlay();
	
	UArcECSSubsystem* CoreSubsystem = UWorld::GetSubsystem<UArcECSSubsystem>(GetWorld());
	FArcUniverse* Universe = CoreSubsystem ? &CoreSubsystem->GetUniverse() : nullptr;
	if (FNephBoardEvents* BoardEvents = Universe ? Universe->GetResource<FNephBoardEvents>() : nullptr)
	{
		BoardEvents->BoardCreatedEvents.Emplace(this);
	}
}

void ANephBoardActor::SetupCollisionPlane() const
{
	if (!CollisionPlane) { return; }

	const FVector PlaneLocation = FVector(
		(GridSizeX * TileSize / 2) - TileSize / 2,
		(GridSizeY * TileSize / 2) - TileSize / 2,
		0.1);
	
	CollisionPlane->SetRelativeLocation(PlaneLocation);
	CollisionPlane->SetWorldScale3D(FVector(GridSizeX, GridSizeY, 1.0f));
	CollisionPlane->SetVisibility(bShowCollisionPlane);
}

void ANephBoardActor::GenerateBoard()
{
	const UWorld* World = GetWorld();
	if (!World) { return; }

	UArcECSSubsystem* CoreSubsystem = UWorld::GetSubsystem<UArcECSSubsystem>(GetWorld());
	FArcUniverse* Universe = CoreSubsystem ? &CoreSubsystem->GetUniverse() : nullptr;
	if (FNephBoardEvents* BoardEvents = Universe ? Universe->GetResource<FNephBoardEvents>() : nullptr)
	{
		BoardEvents->bRegenerateBoardCommand = true;
	}
	
	GetDataFromTileActor();

	SetupCollisionPlane();
	
	const FVector& Center = GetActorLocation();
	BoardCenterLocation = Center;

	BoardTiles.Reset();
	BoardTiles.AddZeroed(GridSizeX * GridSizeY);
	for (int32 x = 0; x < GridSizeX; ++x)
	{
		for (int32 y = 0; y < GridSizeY; ++y)
		{
			const int32 index = x + (y * GridSizeX);
			
			BoardTiles[index] = FNephTileData(x, y);
			BoardTiles[index].TileActor = SpawnTileAtLocation(GetTileLocation(x, y));
		}
	}
}

void ANephBoardActor::DrawBoard() const
{
	const UWorld* World = GetWorld();
	const ANephWorldSettings* worldSettings = World ? Cast<ANephWorldSettings>(World->GetWorldSettings()) : nullptr;
	if (!worldSettings) { return; }

	const FVector tileExtent = FVector(TileSize / 2.f, TileSize / 2.f, 0.f);

	//const FBoxSphereBounds& bounds = GetBounds();
	const float gridHeight = GetActorLocation().Z;//bounds.BoxExtent.Z;

	for (int32 x = 0; x < GridSizeX; ++x)
	{
		for (int32 y = 0; y < GridSizeY; ++y)
		{
			FColor tileColor = FColor::Yellow;

			FVector tileLocation = GetTileLocation(x, y);
			tileLocation.Z = gridHeight;
			DrawDebugBox(World, tileLocation, tileExtent, FQuat::Identity, tileColor, false, 60.f);
			DrawDebugSphere(World, tileLocation, 20.f, 15, tileColor, false, 60.f);
		}
	}
}

const FNephTileData& ANephBoardActor::GetTileAtLocationClamped(const FVector& location) const
{
	const float startTileX = (BoardCenterLocation.X - ((GridSizeX / 2) * TileSize));
	const float startTileY = (BoardCenterLocation.Y - ((GridSizeY / 2) * TileSize));
	const int32 tileX = FMath::Clamp(FMath::FloorToInt((location.X - startTileX) / TileSize), 0, GridSizeX - 1);
	const int32 tileY = FMath::Clamp(FMath::FloorToInt((location.Y - startTileY) / TileSize), 0, GridSizeY - 1);
	const int32 index = (tileX + (tileY * GridSizeX));
	return BoardTiles[index];
}

const FNephTileData* ANephBoardActor::FindTileAtLocation(const FVector& location) const
{
	const FIntPoint coords = GetTileCoordinatesAtLocation(location);
	const int32 index = GetTileIndex(coords.X, coords.Y);
	return BoardTiles.IsValidIndex(index) ? &BoardTiles[index] : nullptr;
}

FVector ANephBoardActor::GetTileLocation(int32 x, int32 y) const
{
	const float tileExtent = TileSize / 2.f;
	return FVector((x * TileSize) + tileExtent, (y * TileSize) + tileExtent, 0.f) + 
		FVector(BoardCenterLocation.X, BoardCenterLocation.Y, 0.f) - 
		FVector(GridSizeX * tileExtent, GridSizeY * tileExtent, 0.f);
}

FIntPoint ANephBoardActor::GetTileCoordinatesAtLocation(const FVector& location) const
{
	if (!ensure(TileSize > 0)) { return FIntPoint(INDEX_NONE, INDEX_NONE); }

	const float startTileX = (BoardCenterLocation.X - ((GridSizeX / 2) * TileSize));
	const float startTileY = (BoardCenterLocation.Y - ((GridSizeY / 2) * TileSize));
	const int32 tileX = FMath::FloorToInt((location.X - startTileX) / TileSize);
	const int32 tileY = FMath::FloorToInt((location.Y - startTileY) / TileSize);

	return FIntPoint(tileX, tileY);
}

void ANephBoardActor::GetDataFromTileActor()
{
	UWorld* World = GetWorld();
	if (!World) { return; }
	ANephTileActor* DefaultTileActor = World->SpawnActor<ANephTileActor>(DefaultTileClass, FVector::ZeroVector, FRotator::ZeroRotator);
	DefaultTileActor->SetActorHiddenInGame(true);
	
	const UStaticMesh* TileMesh =  DefaultTileActor->GetHexMesh();
	
	TileSize = TileMesh ? TileMesh->GetBoundingBox().Max.X * 2: 100;
}

ANephTileActor* ANephBoardActor::SpawnTileAtLocation(const FVector& Location)
{
	UWorld* World = GetWorld();
	if (!World) { return nullptr; }
	ANephTileActor* DefaultTileActor = World->SpawnActor<ANephTileActor>(DefaultTileClass, Location, FRotator::ZeroRotator);
	DefaultTileActor->AttachToActor(this, FAttachmentTransformRules::KeepRelativeTransform);
	return DefaultTileActor;
}
