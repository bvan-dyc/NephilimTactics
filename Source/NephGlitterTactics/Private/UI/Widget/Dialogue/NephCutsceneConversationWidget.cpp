#include "UI\Widget\Dialogue\NephCutsceneConversationWidget.h"

#include "UI/Resource/NephWidgetData.h"
#include "UI/Widget/Dialogue/NephCutsceneSpeakerWidget.h"
#include "UI\Widget\Dialogue\NephDialogueBubbleWidget.h"

void UNephCutsceneConversationWidget::NativeOnInitialized()
{
	Super::NativeOnInitialized();

	if (FNephWidgetData* WidgetData = FNephWidgetData::Get(this))
	{
		WidgetData->CutsceneConversationWidget = this;
	}

	CloseCutscene();
}
/**
void UNephCutsceneConversationWidget::StartDialogue(const UNepDialogueDataAsset* dialogue) const
{
	if (!dialogue)
	{
		CloseCutscene();
		
		return;
	}
	
	if (DialogueBubbleWidget)
	{
		DialogueBubbleWidget->ShowMessage(dialogue);
	}

	if (LeftHandSpeaker)
	{
		LeftHandSpeaker->SetImage(dialogue->Speaker ? dialogue->Speaker->CharacterImage : nullptr);
		LeftHandSpeaker->SetVisibility(dialogue->Speaker ? ESlateVisibility::SelfHitTestInvisible : ESlateVisibility::Hidden);
	}

	if (RightHandSpeaker)
	{
		//@@TODO(vandyck) hide since not yet implemented
		RightHandSpeaker->SetVisibility(ESlateVisibility::Hidden);
	}
}

void UNephCutsceneConversationWidget::FillWithData(const FText& speakerName, const FText& dialogueText, const UNepSpeakerDataAsset* leftHandSpeaker, const UNepSpeakerDataAsset* rightHandSpeaker) const
{
	if (DialogueBubbleWidget)
	{
		DialogueBubbleWidget->SetTitle(speakerName);
		DialogueBubbleWidget->SetDialogue(dialogueText);
	}

	if (LeftHandSpeaker)
	{
		LeftHandSpeaker->SetImage(leftHandSpeaker ? leftHandSpeaker->CharacterImage : nullptr);
		LeftHandSpeaker->SetVisibility(leftHandSpeaker ? ESlateVisibility::SelfHitTestInvisible : ESlateVisibility::Hidden);
	}

	if (RightHandSpeaker)
	{
		RightHandSpeaker->SetImage(rightHandSpeaker ? rightHandSpeaker->CharacterImage : nullptr);
		RightHandSpeaker->SetVisibility(rightHandSpeaker ? ESlateVisibility::SelfHitTestInvisible : ESlateVisibility::Hidden);
	}
}
*/
void UNephCutsceneConversationWidget::EndConversation() const
{
	CloseCutscene();
}

void UNephCutsceneConversationWidget::NativeConstruct()
{
	Super::NativeConstruct();
}

void UNephCutsceneConversationWidget::CloseCutscene() const
{
	if (DialogueBubbleWidget)
	{
		DialogueBubbleWidget->SetVisibility(ESlateVisibility::Hidden);
	}
	
	if (LeftHandSpeaker)
	{
		LeftHandSpeaker->SetVisibility(ESlateVisibility::Hidden);
	}
	
	if (RightHandSpeaker)
	{
		RightHandSpeaker->SetVisibility(ESlateVisibility::Hidden);
	}
}
