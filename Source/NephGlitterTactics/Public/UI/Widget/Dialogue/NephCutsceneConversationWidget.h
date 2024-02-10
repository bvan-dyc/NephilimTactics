#pragma once

#include "CoreMinimal.h"

#include "Blueprint/UserWidget.h"

#include "NephCutsceneConversationWidget.generated.h"

UCLASS()
class NEPHGLITTERTACTICS_API UNephCutsceneConversationWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	
	//void StartDialogue(const UNepDialogueDataAsset* dialogue) const;
	
//	void FillWithData(const FText& speakerName, const FText& dialogueText, const UNepSpeakerDataAsset* leftHandSpeaker, const UNepSpeakerDataAsset* rightHandSpeaker) const;

	void EndConversation() const;

protected:

	UPROPERTY(meta = (BindWidget))
	class UNephDialogueBubbleWidget* DialogueBubbleWidget = nullptr;
	
	UPROPERTY(meta = (BindWidget))
	class UNephCutsceneSpeakerWidget* LeftHandSpeaker = nullptr;

	UPROPERTY(meta = (BindWidget))
	class UNephCutsceneSpeakerWidget* RightHandSpeaker = nullptr;
		
	virtual void NativeOnInitialized() override;
	virtual void NativeConstruct() override;
	void CloseCutscene() const;
};
