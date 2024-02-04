#include "ArcEntityBuilder.h"
#include "ArcUniverse.h"
#include "ArcCommands.h"
#include "Units/Actor/NephUnitPawn.h"
#include "Units/ActorComponent/NephCharacterComponent.h"
#include "Units/Resource/NephUnitsEvents.h"

UNephCharacterComponent::UNephCharacterComponent()
{
    SetIsReplicatedByDefault(true);
    bReplicateUsingRegisteredSubObjectList = true;
}

void UNephCharacterComponent::AddComponentsToEntity(FArcUniverse& Universe, FArcEntityHandle& Entity)
{
    ANephUnitPawn* Character = Cast<ANephUnitPawn>(GetOwner());
    if (!Character || !ensure(Universe.IsValid(Entity))) { return; }
    
    Universe.GetCommands().AddComponent(Entity, FNephUnitData(Data));
    
    if (FNephUnitsEvents* Events = Universe.GetResource<FNephUnitsEvents>())
    {
        Events->CharacterCreatedEvents.Emplace(Entity, Character);
    }
}

void UNephCharacterComponent::RemoveComponentsFromEntity(FArcUniverse& Universe, FArcEntityHandle& Entity)
{
    Universe.GetCommands().RemoveComponent<FNephUnitData>(Entity);
}

void UNephCharacterComponent::OnRegister()
{
    Super::OnRegister();
}

void UNephCharacterComponent::OnUnregister()
{
    Super::OnUnregister();
}
