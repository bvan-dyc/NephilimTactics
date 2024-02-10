#pragma once

#include "CoreMinimal.h"

#include "Blueprint/UserWidget.h"

#include "NephCutsceneSpeakerWidget.generated.h"

UCLASS()
class NEPHGLITTERTACTICS_API UNephCutsceneSpeakerWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	
	void SetImage(UTexture2D* image) const;

	void HideSpeaker();

protected:

	UPROPERTY(meta = (BindWidget))
	class UImage* SpeakerImage;
};
