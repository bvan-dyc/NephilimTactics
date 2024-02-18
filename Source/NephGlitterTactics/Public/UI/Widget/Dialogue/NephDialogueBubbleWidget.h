#pragma once

#include "CoreMinimal.h"

#include "Blueprint/UserWidget.h"

#include "NephDialogueBubbleWidget.generated.h"

UCLASS()
class NEPHGLITTERTACTICS_API UNephDialogueBubbleWidget : public UUserWidget
{
    GENERATED_BODY()

public:

    void ShowDialogue(const struct FNephDialogueData* dialogue);
    void SetTitle(const FText& title) const;
    void SetDialogue(const FText& dialogue) const;
    void SetImage(UTexture2D* image) const;

    void CloseBubble();

protected:

    UPROPERTY(meta = (BindWidgetOptional))
    class UCommonTextBlock* Title;

    UPROPERTY(meta = (BindWidgetOptional))
    class UCommonTextBlock* Content;

    UPROPERTY(meta = (BindWidgetOptional))
    class UImage* SpeakerImage;
};
