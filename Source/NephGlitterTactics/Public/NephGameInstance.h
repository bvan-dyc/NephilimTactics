#pragma once

#include "CoreMinimal.h"
#include "Engine/World.h"
#include "Engine/GameInstance.h"
#include "NephGameInstance.generated.h"

UCLASS()
class NEPHGLITTERTACTICS_API USPNephGameInstance : public UGameInstance
{
	GENERATED_BODY()

public:
	
	virtual void Init() override;
	
	class UNephGameHUD* GetGameHUDWidget() const;
};
