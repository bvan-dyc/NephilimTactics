#include "UI/NephHUD.h"

#include "UI/NephGameHUD.h"

void ANephHUD::BeginPlay()
{
	Super::BeginPlay();

	GameHUD = CreateWidget<UNephGameHUD>(GetWorld(), MainHUDWidget);
	if (GameHUD)
	{
		GameHUD->AddToViewport();
		GameHUD->SetVisibility(ESlateVisibility::Visible);
	}
}

UNephGameHUD* ANephHUD::GetHUDWidget() const
{
	return GameHUD;
}
