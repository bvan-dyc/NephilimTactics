#include "Narrative\System\NephConversationUISystems.h"

#include "Narrative/Resource/NephNarrativeEvents.h"
#include "UI/Widget/Dialogue/NephConversationWidget.h"
#include "UI/Widget/Dialogue/NephCutsceneConversationWidget.h"

void FNephConversationUISystems::ConversationPanelTick(FArcRes<FNephWidgetData> WidgetData, FArcRes<FNephNarrativeEvents> NarrativeEvents)
{
	/**
	for (const FNepShowDialogueRequest& dialogueRequest : NarrativeEvents->ShowOverworldDialogueRequests)
	{
		if (const UNephConversationWidget* conversationWidget = WidgetData->ConversationWidget.Get())
		{
			if (dialogueRequest.DialogueDataAsset)
			{
				conversationWidget->StartDialogue(dialogueRequest.DialogueDataAsset);
			}
			else
			{
				conversationWidget->EndConversation();
			}
		}
	}
	*/
}

void FNephConversationUISystems::CutscenePanelTick(FArcRes<FNephWidgetData> WidgetData, FArcRes<FNephNarrativeEvents> NarrativeEvents)
{
	/**
	for (const FNepShowDialogueRequest& dialogueRequest : NarrativeEvents->ShowCutsceneDialogueRequests)
	{
		if (const UNephCutsceneConversationWidget* conversationWidget = WidgetData->CutsceneConversationWidget.Get())
		{
			if (dialogueRequest.DialogueDataAsset)
			{
				conversationWidget->StartDialogue(dialogueRequest.DialogueDataAsset);
			}
			else
			{
				conversationWidget->EndConversation();
			}
		}
	}
	*/
}
