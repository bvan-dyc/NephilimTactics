#include "Board/System/NephBoardSystems.h"

#include "EngineUtils.h"
#include "Board/Resource/NephBoard.h"
#include "Board/NephTileData.h"
#include "Board/Actor/NephBoardActor.h"
#include "Board/DataAssets/NephLevelGlobalsDataAsset.h"
#include "Board/Resource/NephBoardEvents.h"
#include "Board/Resource/NephLevelGlobals.h"
#include "Resource/ArcCoreData.h"

void FNephBoardSystems::InitializeGlobals(FArcRes<FArcCoreData> CoreData, FArcRes<FNephLevelGlobals> LevelGlobals)
{
	TArray<UObject*> Assets;
	EngineUtils::FindOrLoadAssetsByPath(TEXT("/Game/Globals"), Assets, EngineUtils::ATL_Regular);
	for (UObject* Asset : Assets)
	{
		if (const UNephLevelGlobalsDataAsset* LevelGlobalsDataAsset = Cast<UNephLevelGlobalsDataAsset>(Asset))
		{
			*LevelGlobals = LevelGlobalsDataAsset->LevelGlobals;
		}
	}
}

void FNephBoardSystems::HandleBoardCreatedEvent(FArcRes<FArcCoreData> CoreData, FArcRes<FNephBoard> Board, FArcRes<FNephBoardEvents> BoardEvents, FArcRes<FNephLevelGlobals> LevelGlobals)
{
	if (BoardEvents->BoardCreatedEvents.Num() < 1) { return; }
	
	for (const TWeakObjectPtr<ANephBoardActor> BoardCreated : BoardEvents->BoardCreatedEvents)
	{
		Board->BoardActor = BoardCreated;

		GenerateBoard(CoreData->World.Get(), Board, LevelGlobals);
	}
}

void FNephBoardSystems::HandleHoverOverTileCommands(FArcRes<FArcCoreData> CoreData, FArcRes<FNephBoard> Board, FArcRes<FNephBoardEvents> BoardEvents)
{
	if (!BoardEvents->HoverOverTileCommand.IsSet()) { return; }

	AActor* TileSelectorActor = Board->TileSelectorActor.IsValid() ? Board->TileSelectorActor.Get() : nullptr;
	if (!TileSelectorActor) { return; }

	const FVector SnapLocation = Board->GetTileSnapLocation(BoardEvents->HoverOverTileCommand.GetValue());
	TileSelectorActor->SetActorLocation(SnapLocation);
	Board->SelectedTile = BoardEvents->HoverOverTileCommand.GetValue();
}

void FNephBoardSystems::UpdateHoveredTile(FArcRes<FArcCoreData> CoreData, FArcRes<FNephBoard> Board)
{
	const UWorld* World = CoreData->World.IsValid() ? CoreData->World.Get() : nullptr;
	const APlayerController* PlayerController = World ? World->GetFirstPlayerController() : nullptr;
	if (!PlayerController) { return; }
	
	FHitResult HitResult;
	const bool bHitSuccessful = PlayerController->GetHitResultUnderCursor(ECollisionChannel::ECC_Visibility, false, HitResult);
	if (!bHitSuccessful) { return; }
	
	const FNephTileData* TileAtLocation = Board->FindTileAtLocation(HitResult.ImpactPoint);
	if (!TileAtLocation) { return; }
	AActor* TileSelectorActor = Board->TileSelectorActor.IsValid() ? Board->TileSelectorActor.Get() : nullptr;
	if (!TileSelectorActor) { return; }

	const FVector SnapLocation = Board->GetTileSnapLocation(TileAtLocation->TileCoordinates);
	TileSelectorActor->SetActorLocation(SnapLocation);
	Board->SelectedTile = TileAtLocation->TileCoordinates;
}

void FNephBoardSystems::GenerateBoard(const UWorld* World, FArcRes<FNephBoard>& Board, const FArcRes<FNephLevelGlobals> LevelGlobals)
{
	if (!World) { return; }

	const ANephBoardActor* BoardActor = Board->BoardActor.IsValid() ? Board->BoardActor.Get() : nullptr;
	if (!BoardActor) { return; }

	Board->InitFromActor(BoardActor);
}

void FNephBoardSystems::ClearEvents(FArcRes<FNephBoardEvents> Events)
{
	*Events = FNephBoardEvents();
}

void FNephBoardSystems::InitBoardUI(FArcRes<FArcCoreData> CoreData, FArcRes<FNephBoard> Board, const FArcRes<FNephLevelGlobals> LevelGlobals)
{
	UWorld* World = CoreData->World.Get();
	if (!World) { return; }
	
	Board->TileSelectorActor = World->SpawnActor<AActor>(LevelGlobals->TileSelectorClass, FTransform(FVector::ZeroVector));
}
