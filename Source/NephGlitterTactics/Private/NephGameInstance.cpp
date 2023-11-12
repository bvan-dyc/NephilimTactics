#include "NephGameInstance.h"

#include "NephPlayerController.h"
#include "UI/NephHUD.h"

void USPNephGameInstance::Init()
{
	Super::Init();
}

UNephGameHUD* USPNephGameInstance::GetGameHUDWidget() const
{
	const ANephPlayerController* PlayerController = Cast<ANephPlayerController>(GetWorld()->GetFirstPlayerController());
	const ANephHUD* HUD = PlayerController ? Cast<ANephHUD>(PlayerController->GetHUD()) : nullptr;
	return HUD ? HUD->GetHUDWidget() : nullptr;
}
