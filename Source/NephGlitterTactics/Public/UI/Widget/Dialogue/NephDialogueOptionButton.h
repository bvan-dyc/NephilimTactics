#pragma once

#include "CoreMinimal.h"

#include "Blueprint/UserWidget.h"

#include "NephDialogueOptionButton.generated.h"

UCLASS()
class NEPHGLITTERTACTICS_API UNephDialogueOptionButton : public UUserWidget
{
	GENERATED_BODY()

public:

	void SetText();

protected:

	UPROPERTY(meta = (BindWidget))
	class UCommonTextBlock* ButtonText;
};
