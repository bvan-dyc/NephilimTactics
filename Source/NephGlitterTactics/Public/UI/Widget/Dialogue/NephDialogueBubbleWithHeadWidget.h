#pragma once

#include "CoreMinimal.h"

#include "Blueprint/UserWidget.h"

#include "NephDialogueBubbleWithHeadWidget.generated.h"

UCLASS()
class NEPHGLITTERTACTICS_API UNephDialogueBubbleWithHeadWidget : public UUserWidget
{
    GENERATED_BODY()

public:
/**
    void ShowMessage(const UNepDialogueDataAsset* dialogueDat);
*/
    void SetTitle(const FText& title) const;
    void SetDialogue(const FText& dialogue) const;
    void SetImage(UTexture2D* image) const;
    
    void CloseBubble();

protected:

    UPROPERTY(meta = (BindWidget))
    class UCommonTextBlock* Title;

    UPROPERTY(meta = (BindWidget))
    class UCommonTextBlock* Content;

    UPROPERTY(meta = (BindWidget))
    class UImage* SpeakerImage;
};
