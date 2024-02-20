#include "NephGameInstance.h"

#include "NephPlayerController.h"
#include "UI/NephHUD.h"

void UNephGameInstance::Init()
{
	Super::Init();
}

UNephGameHUD* UNephGameInstance::GetGameHUDWidget() const
{
	const ANephPlayerController* PlayerController = Cast<ANephPlayerController>(GetWorld()->GetFirstPlayerController());
	const ANephHUD* HUD = PlayerController ? Cast<ANephHUD>(PlayerController->GetHUD()) : nullptr;
	return HUD ? HUD->GetHUDWidget() : nullptr;
}
