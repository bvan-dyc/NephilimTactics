#pragma once

#include "NephFlowNode.h"
#include "Narrative/NephSpeakerDataAsset.h"
#include "NephFlowNodePlayDialogue.generated.h"

UCLASS(NotBlueprintable, meta = (DisplayName = "Play Dialogue"))
class NEPHGLITTERTACTICS_API UNephFlowNodePlayDialogue : public UNephFlowNode
{
	GENERATED_BODY()

public:

	UNephFlowNodePlayDialogue();
	
	virtual void ExecuteInput(const FName& PinName) override;

#if WITH_EDITOR
	virtual void PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent) override;
	virtual void PostEditChangeChainProperty(FPropertyChangedChainEvent& PropertyChangedEvent) override;
#endif //WITH_EDITOR
	
	void RegenerateOutputPins();
	
	FText GetReadableDialogueString() const { return DialogueTextContent; };
	FText GetSpeakerName() const { return SpeakerDataAsset ? SpeakerDataAsset->SpeakerName : FText::GetEmpty(); }
	FLinearColor GetSpeakerColor() const { return SpeakerDataAsset ? SpeakerDataAsset->SpeakerColor : FLinearColor::Gray; };
	UTexture2D* GetSpeakerPortrait() const { return SpeakerDataAsset ? SpeakerDataAsset->SpeakerImage : nullptr; }

protected:

	static const FText Continue;

	UPROPERTY(EditAnywhere)
	FText SpeakerEmotion;
	
	UPROPERTY(EditAnywhere, meta=(MultiLine=true))
	FText DialogueTextContent = FText::GetEmpty();

	UPROPERTY(EditAnywhere, meta=(TitleProperty="DialogueOption"))
	TArray<FText> NarrativeOutputPins;
	
	UPROPERTY(EditAnywhere)
	class UNephSpeakerDataAsset* SpeakerDataAsset = nullptr;
	
	FDelegateHandle NextDialogueHandle;
	FDelegateHandle ConversationEndedHandle;
};
