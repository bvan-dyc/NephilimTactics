#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "NephConversationWidget.generated.h"

UCLASS()
class NEPHGLITTERTACTICS_API UNephConversationWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	
	//void StartDialogue(const UNepDialogueDataAsset* dialogue) const;
	
	void FillWithData(const FText& speakerName, const FText& dialogueText, UTexture2D* speaker) const;
	void EndConversation() const;
	
protected:

	virtual void NativeOnInitialized() override;
	virtual void NativeConstruct() override;

	UPROPERTY(meta = (BindWidget))
	class UNephDialogueBubbleWidget* DialogueBubbleWidget = nullptr;
};
