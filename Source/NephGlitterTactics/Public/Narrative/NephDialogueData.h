#pragma once

struct FNephDialogueData
{
	
public:

	FText SpeakerEmotion;
	
	class UNephSpeakerDataAsset* Speaker = nullptr;
	
	FText DialogueTextContent = FText::GetEmpty();

	TArray<FText> NarrativeOutputPins;
};
