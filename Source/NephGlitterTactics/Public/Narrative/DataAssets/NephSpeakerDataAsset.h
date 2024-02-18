#pragma once

#include "Engine/DataAsset.h"

#include "NephSpeakerDataAsset.generated.h"

UCLASS()
class NEPHGLITTERTACTICS_API UNephSpeakerDataAsset : public UDataAsset
{
	GENERATED_BODY()

public:

	UPROPERTY(EditDefaultsOnly)
	FText SpeakerName;
	
	UPROPERTY(EditDefaultsOnly)
	class UTexture2D* SpeakerImage;

	UPROPERTY(EditDefaultsOnly)
	FLinearColor SpeakerColor = FLinearColor::Gray;
};
