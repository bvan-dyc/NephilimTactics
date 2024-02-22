#include "Units/System/NephUnitsSystems.h"

#include "Board/Resource/NephBoard.h"
#include "Units/Actor/NephCharacter.h"
#include "Units/Component/NephUnitData.h"
#include "Units/Resource/NephUnitsEvents.h"
#include "ArcEntityHandle.h"

void FNephUnitsSystems::SnapUnitsToBoard(FArcRes<FNephBoard> Board, FArcRes<FNephUnitsEvents> UnitEvents)
{
	for (TPair<FArcEntityHandle, TWeakObjectPtr<ANephCharacter>>& UnitCreatedEvent : UnitEvents->CharacterCreatedEvents)
	{
		ANephCharacter* Unit = UnitCreatedEvent.Value.Get();
		if (!Unit) { continue; }

		const FIntPoint UnitTileCoords = Board->GetTileCoordinatesAtLocation(Unit->GetActorLocation());
		
		Unit->SetActorLocation(Board->GetTileSnapLocation(UnitTileCoords));
	}
}

void FNephUnitsSystems::HandlePlaceEntityOnTileCommands(const FArcUniverse& Universe, FArcRes<FNephUnitsEvents> Events, FArcRes<FNephBoard> Board)
{
	for (TPair<FArcEntityHandle, FIntPoint>& PlaceUnitOnTileCommand : Events->PlaceUnitOnTileCommands)
	{
		const FArcEntityHandle& Entity = PlaceUnitOnTileCommand.Get<0>();
		const FNephUnitData* UnitData = Entity.GetComponent<FNephUnitData>(Universe);
		ANephCharacter* UnitActor = UnitData->UnitActor.IsValid() ? UnitData->UnitActor.Get() : nullptr;
		if (!UnitActor) { continue; }
		
		FNephTileData* TileAtCoordinates = Board->GetTileWithCoordinates( PlaceUnitOnTileCommand.Get<1>());
		if (!TileAtCoordinates) { continue; }

		TileAtCoordinates->TileContent = Entity;
		
		UnitActor->SetActorLocation(Board->GetTileSnapLocation(TileAtCoordinates->TileCoordinates));
	}
}

void FNephUnitsSystems::ClearEvents(FArcRes<FNephUnitsEvents> Events)
{
	*Events = FNephUnitsEvents();
}
