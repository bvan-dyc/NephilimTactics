#include "UI\Widget\Dialogue\NephDialogueBubbleWidget.h"

#include "CommonTextBlock.h"
#include "Components/Image.h"
#include "Narrative/NephDialogueData.h"
#include "Narrative/DataAssets/NephSpeakerDataAsset.h"

void UNephDialogueBubbleWidget::ShowDialogue(const FNephDialogueData* dialogue)
{
	SetVisibility(dialogue ? ESlateVisibility::SelfHitTestInvisible : ESlateVisibility::Hidden);

	if (Title)
	{
		Title->SetText(dialogue->Speaker ? dialogue->Speaker->SpeakerName : FText::GetEmpty());
	}
	if (Content)
	{
		Content->SetText(dialogue->DialogueTextContent);
	}
	if (SpeakerImage)
	{
		SpeakerImage->SetBrushFromTexture(dialogue->Speaker ? dialogue->Speaker->SpeakerImage : nullptr);
	}
}

void UNephDialogueBubbleWidget::SetTitle(const FText& title) const
{
	if (Title)
	{
		Title->SetText(title);
	}
}

void UNephDialogueBubbleWidget::SetDialogue(const FText& dialogue) const
{
	if (Content)
	{
		Content->SetText(dialogue);
	}
}

void UNephDialogueBubbleWidget::SetImage(UTexture2D* image) const
{
	if (SpeakerImage)
	{
		SpeakerImage->SetBrushFromTexture(image);
	}
}

void UNephDialogueBubbleWidget::CloseBubble()
{
	SetVisibility(ESlateVisibility::Hidden);
}
