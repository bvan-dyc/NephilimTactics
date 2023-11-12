#include "Narrative\Flow\NephFlowNodePlayDialogue.h"

const FText UNephFlowNodePlayDialogue::Continue = FText::FromString(FString(TEXT("Next")));

UNephFlowNodePlayDialogue::UNephFlowNodePlayDialogue()
{
#if WITH_EDITOR
    Category = TEXT("Narrative");
#endif //WITH_EDITOR

    RegenerateOutputPins();
}

void UNephFlowNodePlayDialogue::ExecuteInput(const FName& PinName)
{
    Super::ExecuteInput(PinName);
}

#if WITH_EDITOR
void UNephFlowNodePlayDialogue::PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent)
{
    UFlowNode::PostEditChangeProperty(PropertyChangedEvent);
    
    RegenerateOutputPins();
}

void UNephFlowNodePlayDialogue::PostEditChangeChainProperty(FPropertyChangedChainEvent& PropertyChangedEvent)
{
    Super::PostEditChangeChainProperty(PropertyChangedEvent);

    if (PropertyChangedEvent.GetPropertyName() == GET_MEMBER_NAME_CHECKED(UNephFlowNodePlayDialogue, NarrativeOutputPins))
    {
        RegenerateOutputPins();
        OnReconstructionRequested.ExecuteIfBound();
    }
}
#endif //WITH_EDITOR

void UNephFlowNodePlayDialogue::RegenerateOutputPins()
{
    OutputPins.Empty();

    if (!NarrativeOutputPins.Num())
    {
        OutputPins.Add({ Continue });
    }
    
    for (FText NarrativePin : NarrativeOutputPins)
    {
        OutputPins.Add(FFlowPin(NarrativePin.ToString()));
    }
}
