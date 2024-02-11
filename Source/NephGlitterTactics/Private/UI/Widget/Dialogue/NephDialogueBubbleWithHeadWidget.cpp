#include "UI\Widget\Dialogue\NephDialogueBubbleWithHeadWidget.h"

#include "CommonTextBlock.h"
#include "Components/Image.h"

#include "Components/TextBlock.h"

/**
void UNephDialogueBubbleWithHeadWidget::ShowMessage(const UNephDialogueDataAsset* dialogue)
{
	SetVisibility(dialogue ? ESlateVisibility::SelfHitTestInvisible : ESlateVisibility::Hidden);

	if (Title)
	{
		Title->SetText(dialogue->Speaker ? dialogue->Speaker->SpeakerName : FText::GetEmpty());
	}
	if (Content)
	{
		Content->SetText(dialogue->Text);
	}
	if (SpeakerImage)
	{
		SpeakerImage->SetBrushFromTexture(dialogue->Speaker ? dialogue->Speaker->CharacterImage : nullptr);
	}
}
*/
void UNephDialogueBubbleWithHeadWidget::SetTitle(const FText& title) const
{
	if (Title)
	{
		Title->SetText(title);
	}
}

void UNephDialogueBubbleWithHeadWidget::SetDialogue(const FText& dialogue) const
{
	if (Content)
	{
		Content->SetText(dialogue);
	}
}

void UNephDialogueBubbleWithHeadWidget::SetImage(UTexture2D* image) const
{
	if (SpeakerImage)
	{
		SpeakerImage->SetBrushFromTexture(image);
	}
}

void UNephDialogueBubbleWithHeadWidget::CloseBubble()
{
	SetVisibility(ESlateVisibility::Hidden);
}
