#include "UI\Widget\Dialogue\NephConversationWidget.h"

#include "UI/Resource/NephWidgetData.h"
#include "UI\Widget\Dialogue\NephDialogueBubbleWidget.h"

void UNephConversationWidget::FillWithData(const FText& speakerName, const FText& dialogueText, UTexture2D* speaker) const
{
	if (DialogueBubbleWidget)
	{
		DialogueBubbleWidget->SetTitle(speakerName);
		DialogueBubbleWidget->SetDialogue(dialogueText);
		DialogueBubbleWidget->SetImage(speaker);
	}
}
/**
void UNephConversationWidget::StartDialogue(const UNepDialogueDataAsset* dialogue) const
{
	if (!dialogue)
	{
		if (DialogueBubbleWidget)
		{
			DialogueBubbleWidget->CloseBubble();
		}
		
		return;
	}
	
	if (DialogueBubbleWidget)
	{
		DialogueBubbleWidget->ShowMessage(dialogue);
	}
}
*/
void UNephConversationWidget::EndConversation() const
{
	if (DialogueBubbleWidget)
	{
		DialogueBubbleWidget->CloseBubble();
	}
}

void UNephConversationWidget::NativeOnInitialized()
{
	Super::NativeOnInitialized();

	if (FNephWidgetData* WidgetData = FNephWidgetData::Get(this))
	{
		WidgetData->ConversationWidget = this;
	}
	
	if (DialogueBubbleWidget)
	{
		DialogueBubbleWidget->CloseBubble();
	}
}

void UNephConversationWidget::NativeConstruct()
{
	Super::NativeConstruct();
}
