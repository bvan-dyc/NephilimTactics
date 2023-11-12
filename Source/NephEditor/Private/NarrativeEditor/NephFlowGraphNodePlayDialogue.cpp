#include "NarrativeEditor/NephFlowGraphNodePlayDialogue.h"

#include "Narrative/Flow/NephFlowNodePlayDialogue.h"
#include "NarrativeEditor/NephFlowNodeWidgetPlayDialogue.h"

UNephFlowGraphNodePlayDialogue::UNephFlowGraphNodePlayDialogue()
{
	AssignedNodeClasses = { UNephFlowNodePlayDialogue::StaticClass() };
}

TSharedPtr<SGraphNode> UNephFlowGraphNodePlayDialogue::CreateVisualWidget()
{
	return SNew(NephFlowNodeWidgetPlayDialogue, this);
}
