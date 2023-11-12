#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "NephHUD.generated.h"

UCLASS()
class NEPHGLITTERTACTICS_API ANephHUD : public AHUD
{
	GENERATED_BODY()

public:

	class UNephGameHUD* GetHUDWidget() const;

protected:

	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Widgets")
	TSubclassOf<class UNephGameHUD> MainHUDWidget;

	UPROPERTY()
	TObjectPtr<class UNephGameHUD> GameHUD;
};
