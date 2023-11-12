#include "UI/NephGameHUD.h"

#include "NephPlayerController.h"
#include "UI/NephHUD.h"

UNephGameHUD* UNephGameHUD::Get(const UObject* context)
{
	const UWorld* World = context ? context->GetWorld() : nullptr;
	const ANephPlayerController* PlayerController = World ? Cast<ANephPlayerController>(World->GetFirstPlayerController()) : nullptr;
	const ANephHUD* HUD = World ? Cast<ANephHUD>(PlayerController->GetHUD()) : nullptr;
	return HUD ? Cast<UNephGameHUD>(HUD->GetHUDWidget()) : nullptr;
}
